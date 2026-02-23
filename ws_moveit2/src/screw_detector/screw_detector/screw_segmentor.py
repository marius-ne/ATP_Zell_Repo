from typing import Optional

import cv2
import numpy as np
import rclpy
import torch
from ament_index_python.packages import get_package_share_directory
from cv_bridge import CvBridge
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, DurabilityPolicy, HistoryPolicy
from sensor_msgs.msg import Image
from realsense2_camera_msgs.msg import RGBD
from torchvision.models.segmentation import (
    DeepLabV3_ResNet50_Weights,
    deeplabv3_resnet50,
)
from torchvision.transforms import Compose, Normalize, ToTensor


class ScrewSegmentorNode(Node):
    def __init__(self) -> None:
        super().__init__('screw_segmentor_node')

        self.declare_parameter('image_topic', '/camera/camera/rgbd')
        self.declare_parameter('mask_topic', '/screw_segmentor/mask')
        self.declare_parameter('overlay_topic', '/screw_segmentor/overlay')
        self.declare_parameter('device', 'cpu')
        self.declare_parameter('target_class', 1)
        self.declare_parameter('confidence_threshold', 0.5)

        image_topic = self.get_parameter('image_topic').value
        mask_topic = self.get_parameter('mask_topic').value
        overlay_topic = self.get_parameter('overlay_topic').value
        device_name = self.get_parameter('device').value
        self.target_class = int(self.get_parameter('target_class').value)
        self.confidence_threshold = float(self.get_parameter('confidence_threshold').value)

        model_weights_path = "segmentation_model.pth" # Default relative path within the package

        package_share_dir = get_package_share_directory('screw_detector')
        weights_dir = package_share_dir + '/weights'
        resolved_weights_path = self._resolve_weights_path(model_weights_path, weights_dir)

        if device_name == 'cuda' and not torch.cuda.is_available():
            self.get_logger().warning('CUDA requested but unavailable. Falling back to CPU.')
            device_name = 'cpu'
        self.device = torch.device(device_name)

        self.bridge = CvBridge()
        self.model, self.preprocess = self._build_model(resolved_weights_path)
        self.model.to(self.device)
        self.model.eval()

        # RELIABLE subscriber is compatible with RELIABLE publisher.
        # VOLATILE durability is compatible with TRANSIENT_LOCAL publisher.
        # depth=1 so we always process the latest frame only.
        image_qos = QoSProfile(
            reliability=ReliabilityPolicy.RELIABLE,
            durability=DurabilityPolicy.VOLATILE,
            history=HistoryPolicy.KEEP_LAST,
            depth=1,
        )
        self.subscription = self.create_subscription(
            RGBD,
            image_topic,
            self.image_callback,
            image_qos,
        )
        self.mask_publisher = self.create_publisher(Image, mask_topic, 10)
        self.overlay_publisher = self.create_publisher(Image, overlay_topic, 10)

        self.get_logger().info(
            f'Screw segmentor started. Subscribing to {image_topic}, '
            f'publishing mask to {mask_topic}, overlay to {overlay_topic}, device={self.device.type}'
        )

    def _resolve_weights_path(self, raw_path: str, weights_dir: str) -> str:
        if raw_path.startswith('/') or ':' in raw_path:
            return raw_path
        if raw_path.startswith('weights/'):
            return get_package_share_directory('screw_detector') + '/' + raw_path
        return weights_dir + '/' + raw_path


    def _build_model(self, weights_path: str):
        if weights_path:
            try:
                state_dict = torch.load(weights_path, map_location='cpu')
                if isinstance(state_dict, dict):
                    if 'state_dict' in state_dict:
                        state_dict = state_dict['state_dict']
                    elif 'model_state_dict' in state_dict:
                        state_dict = state_dict['model_state_dict']

                # Detect num_classes from the classifier head in the checkpoint
                classifier_weight_key = 'classifier.4.weight'
                if classifier_weight_key in state_dict:
                    num_classes = state_dict[classifier_weight_key].shape[0]
                else:
                    num_classes = 2

                # Detect whether aux_classifier was used during training
                has_aux = any(k.startswith('aux_classifier') for k in state_dict)

                model = deeplabv3_resnet50(
                    weights=None, weights_backbone=None,
                    num_classes=num_classes, aux_loss=has_aux,
                )
                model.load_state_dict(state_dict)

                preprocess = Compose(
                    [
                        ToTensor(),
                        Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
                    ]
                )
                self.get_logger().info(
                    f'Loaded custom DeepLabV3 weights from {weights_path} '
                    f'(num_classes={num_classes}, aux_loss={has_aux})'
                )
                return model, preprocess
            except Exception as error:
                self.get_logger().error(
                    f'Failed to load custom weights from {weights_path}: {error}. Falling back to torchvision default weights.'
                )

        weights = DeepLabV3_ResNet50_Weights.DEFAULT
        model = deeplabv3_resnet50(weights=weights)
        preprocess = weights.transforms()
        self.get_logger().warning(
            'No custom weights provided. Using torchvision default DeepLabV3 weights.'
        )
        return model, preprocess

    @torch.no_grad()
    def image_callback(self, msg: RGBD) -> None:
        try:
            bgr_image = self.bridge.imgmsg_to_cv2(msg.rgb, desired_encoding='bgr8')
        except Exception as error:
            self.get_logger().error(f'Could not convert incoming image: {error}')
            return

        orig_h, orig_w = bgr_image.shape[:2]
        self.get_logger().info(
            f'Processing frame {orig_w}x{orig_h}', throttle_duration_sec=5.0)

        rgb_image = cv2.cvtColor(bgr_image, cv2.COLOR_BGR2RGB)

        # Resize for faster inference on CPU (max 520px on the long side)
        max_side = 520
        scale = min(max_side / orig_w, max_side / orig_h, 1.0)
        if scale < 1.0:
            resized = cv2.resize(rgb_image, None, fx=scale, fy=scale,
                                 interpolation=cv2.INTER_LINEAR)
        else:
            resized = rgb_image

        input_tensor = self.preprocess(resized).unsqueeze(0).to(self.device)
        output = self.model(input_tensor)['out'][0]

        num_classes = output.shape[0]

        if num_classes == 1:
            # Single-channel binary segmentation (sigmoid)
            prob = torch.sigmoid(output[0])
            mask_u8 = (prob >= self.confidence_threshold).cpu().numpy().astype(np.uint8) * 255
        else:
            # Multi-class segmentation (softmax)
            probabilities = torch.softmax(output, dim=0)
            class_map = torch.argmax(probabilities, dim=0)

            if self.target_class >= 0:
                if self.target_class >= num_classes:
                    self.get_logger().error(
                        f'target_class={self.target_class} is out of range for model output with {num_classes} classes.'
                    )
                    return
                target_conf = probabilities[self.target_class]
                binary_mask = (
                    (class_map == self.target_class)
                    & (target_conf >= self.confidence_threshold)
                )
                mask_u8 = (binary_mask.cpu().numpy().astype(np.uint8)) * 255
            else:
                mask_u8 = class_map.cpu().numpy().astype(np.uint8)

        # Resize mask back to original image dimensions
        if mask_u8.shape[:2] != (orig_h, orig_w):
            mask_u8 = cv2.resize(mask_u8, (orig_w, orig_h),
                                 interpolation=cv2.INTER_NEAREST)

        # Publish raw mask
        mask_msg = self.bridge.cv2_to_imgmsg(mask_u8, encoding='mono8')
        mask_msg.header = msg.rgb.header
        self.mask_publisher.publish(mask_msg)

        # Publish red overlay on original image
        overlay = bgr_image.copy()
        mask_bool = mask_u8 > 0
        red_tint = np.zeros_like(overlay)
        red_tint[:, :, 2] = 255  # BGR red channel
        overlay[mask_bool] = cv2.addWeighted(
            overlay[mask_bool], 0.6, red_tint[mask_bool], 0.4, 0
        )
        overlay_msg = self.bridge.cv2_to_imgmsg(overlay, encoding='bgr8')
        overlay_msg.header = msg.rgb.header
        self.overlay_publisher.publish(overlay_msg)


def main(args: Optional[list] = None) -> None:
    rclpy.init(args=args)
    node = ScrewSegmentorNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

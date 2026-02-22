from typing import Optional

import cv2
import numpy as np
import rclpy
import torch
from ament_index_python.packages import get_package_share_directory
from cv_bridge import CvBridge
from rclpy.node import Node
from sensor_msgs.msg import Image
from torchvision.models.segmentation import (
    DeepLabV3_ResNet50_Weights,
    deeplabv3_resnet50,
)
from torchvision.transforms import Compose, Normalize, ToTensor


class ScrewSegmentorNode(Node):
    def __init__(self) -> None:
        super().__init__('screw_segmentor_node')

        self.declare_parameter('image_topic', '/camera/color/image_raw')
        self.declare_parameter('mask_topic', '/screw_segmentor/mask')
        self.declare_parameter('device', 'cpu')
        self.declare_parameter('target_class', 1)
        self.declare_parameter('confidence_threshold', 0.5)

        image_topic = self.get_parameter('image_topic').value
        mask_topic = self.get_parameter('mask_topic').value
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

        self.subscription = self.create_subscription(
            Image,
            image_topic,
            self.image_callback,
            10,
        )
        self.mask_publisher = self.create_publisher(Image, mask_topic, 10)

        self.get_logger().info(
            f'Screw segmentor started. Subscribing to {image_topic}, publishing mask to {mask_topic}, device={self.device.type}'
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
                model = deeplabv3_resnet50(weights=None, weights_backbone=None, num_classes=2)
                state_dict = torch.load(weights_path, map_location='cpu')
                if isinstance(state_dict, dict):
                    if 'state_dict' in state_dict:
                        state_dict = state_dict['state_dict']
                    elif 'model_state_dict' in state_dict:
                        state_dict = state_dict['model_state_dict']
                model.load_state_dict(state_dict)
                preprocess = Compose(
                    [
                        ToTensor(),
                        Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
                    ]
                )
                self.get_logger().info(f'Loaded custom DeepLabV3 weights from {weights_path}')
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
    def image_callback(self, msg: Image) -> None:
        try:
            bgr_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except Exception as error:
            self.get_logger().error(f'Could not convert incoming image: {error}')
            return

        rgb_image = cv2.cvtColor(bgr_image, cv2.COLOR_BGR2RGB)

        input_tensor = self.preprocess(rgb_image).unsqueeze(0).to(self.device)
        output = self.model(input_tensor)['out'][0]

        probabilities = torch.softmax(output, dim=0)
        class_map = torch.argmax(probabilities, dim=0)

        if self.target_class >= 0:
            if self.target_class >= probabilities.shape[0]:
                self.get_logger().error(
                    f'target_class={self.target_class} is out of range for model output with {probabilities.shape[0]} classes.'
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

        mask_msg = self.bridge.cv2_to_imgmsg(mask_u8, encoding='mono8')
        mask_msg.header = msg.header
        self.mask_publisher.publish(mask_msg)


def main(args: Optional[list] = None) -> None:
    rclpy.init(args=args)
    node = ScrewSegmentorNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

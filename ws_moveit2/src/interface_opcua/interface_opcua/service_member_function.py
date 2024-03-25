from wzlscheduler_interfaces.srv import SetValueIoInterface 

import rclpy
from rclpy.node import Node


class OpcUaClient(Node):

    def __init__(self):
        super().__init__('Ros_Io_OpcUa_Client_Service')
        self.srv = self.create_service(SetValueIoInterface, 'set_value_io_interface', self.set_value_io_interface_callback)

    def set_value_io_interface_callback(self, request, response):
        response.result = True
        self.get_logger().info('Incoming request\nSlotIndex: %d Index: %d' % (request.slotindex, request.value))

        return response


def main():
    rclpy.init()

    opcua_client = OpcUaClient()
    opcua_client.get_logger().info("Start Ros OPC UA Client")

    rclpy.spin(opcua_client)

    rclpy.shutdown()


if __name__ == '__main__':
    main()
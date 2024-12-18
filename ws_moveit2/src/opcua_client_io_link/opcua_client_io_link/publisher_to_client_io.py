#!usr/bin/env python3
import rclpy
from rclpy.node import Node
from opcua_interfaces_io_link.msg import SensorRead, SensorReadRequest
import time

class publisher_to_client_io(Node):

    def __init__(self):
        super().__init__("publisher_to_client_io")

        ## Connect to Topic

        self.read_request_publish = self.create_publisher(SensorReadRequest, "Sensor_Read_Request", 10)
        
        self.read_receive_subscriber = self.create_subscription(SensorRead, "Sensor_Read",
             self.read_receive, 10)
        
        time.sleep(1)
        
        self.get_logger().info("STARTED")

        ## READ EXAMPLE ##
        
        ## Sensor Read Types
        # Type 1: Single Boolean e.g. Alarm
        # Type 2: int e.g. Tuer
        
        ## Define Read Request
        msg_read_request = SensorReadRequest()
        msg_read_request.sensor_id = 'ns=4;i=5008' # Sensor ID
        msg_read_request.sensor_read_type = 1

        ## Send Read Request
        self.read_request_publish.publish(msg_read_request)
        self.get_logger().info("Read MSG Request Sent")

    ## Callback for Read Receiving
    def read_receive(self, msg: SensorRead): 
        self.get_logger().info("Read MSG Received")
        
        if msg.sensor_read_type == 1: #Bool
            print("Sensor ID:", msg.sensor_id)
            print("Sensor Read Type:", msg.sensor_read_type)
            print("Sensor Value:", msg.sensor_value_bool1)
        
        elif msg.sensor_read_type == 2: # uint16
            print("Sensor ID:", msg.sensor_id)
            print("Sensor Read Type:", msg.sensor_read_type)
            print("Sensor Value:", msg.sensor_value_int)

        else:
            print("GIVEN ACTUATOR READ TYPE NOT KNOWN")

def main(args=None):
    rclpy.init(args=args) 

    node = publisher_to_client_io()
    rclpy.spin(node)

    rclpy.shutdown() 
#!usr/bin/env python3
import rclpy
from rclpy.node import Node
from opcua_interfaces_io_link.msg import SensorRead, SensorReadRequest
from opcua import Client
import time


class client_node_io_link(Node):

    def __init__(self):
        super().__init__("client_node_io_link")
        self.get_logger().info("Node Started")
        
        global client
        client = Client("opc.tcp://192.168.13.179:4841")
        client.connect()
        self.get_logger().info("Server Connected")
        
        self.read_request_subscriber = self.create_subscription(SensorReadRequest, "Sensor_Read_Request",
        self.client_read_callback, 10)

        #TODO Rename topic and other stuff
        self.read_publish = self.create_publisher(SensorRead, "Actuator_Read", 10)


        time.sleep(1) # Wait for a second to establish connections


    def client_read_callback(self, msg: SensorReadRequest): # defining Callback for read
        self.get_logger().info("Read Request Msg received")

        #TODO Implement Phyton script for reading the sensor values
        #TODO Publish data to ROS Topic
        '''
        par_object = client.get_node(msg.sensor_id)
        state = client.get_node(par_object.get_children()[1])
        
        read_msg = SensorRead()
        read_msg.sensor_id = msg.sensor_id
        read_msg.sensor_read_type = msg.sensor_read_type
        
        ## Actuator Read Types
        # Type 1: Single Boolean e.g. Alarm
        # Type 2: int e.g. Tuer

        if msg.sensor_read_type == 1:
            read_msg.sensor_value_bool1 =  state.get_value()
            self.get_logger().info("Read Performed")
            
            self.read_publish.publish(read_msg)
            self.get_logger().info("Read MSG Sent")

        elif msg.sensor_read_type == 2: # Tuer uint16 
            read_msg.sensor_value_int = state.get_value()
            self.get_logger().info("Read Performed")
            
            self.read_publish.publish(read_msg)
            self.get_logger().info("Read MSG Sent")

        else:
            print("GIVEN SENSOR READ TYPE NOT KNOWN")
        '''
        
def main(args=None):
    rclpy.init(args=args) 

    node = client_node_io_link()
    rclpy.spin(node)

    rclpy.shutdown() 
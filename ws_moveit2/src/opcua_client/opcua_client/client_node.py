#!usr/bin/env python3
import rclpy
from rclpy.node import Node
from autopilot_interfaces.msg import ActuatorWrite, ActuatorRead, ActuatorReadRequest
from opcua import Client
import time


class client_node(Node):

    def __init__(self):
        super().__init__("client_node")
        self.get_logger().info("Node Started")
        
        global client
        client = Client("opc.tcp://192.168.20.5:4840")
        client.connect()
        self.get_logger().info("Server Connected")

        self.write_subscriber = self.create_subscription(ActuatorWrite, "Actuator_Write",
            self.client_write_callback, 10)
        
        self.read_request_subscriber = self.create_subscription(ActuatorReadRequest, "Actuator_Read_Request",
            self.client_read_callback, 10)
        
        self.read_publish = self.create_publisher(ActuatorRead, "Actuator_Read", 10)

        time.sleep(1) # Wait for a second to establish connections

    def client_write_callback(self, msg: ActuatorWrite): # defining Callback for write
        self.get_logger().info("Write Msg received")

        par_object = client.get_node(msg.actuator_id)
        method = client.get_node(par_object.get_children()[0])

        ## Actuator Write Types
        # Type 1: Single Boolean e.g. Alarm
        # Type 2: Double Boolean e.g. Tuer

        if msg.actuator_write_type == 1: #Bool
            par_object.call_method(method,msg.actuator_command_bool1)
            self.get_logger().info("Write Performed")

        elif msg.actuator_write_type == 2: #Bool Bool
            par_object.call_method(method,msg.actuator_command_bool1, msg.actuator_command_bool2)
            self.get_logger().info("Write Performed")

        else:
            print("GIVEN ACTUATOR TYPE NOT KNOWN")


    def client_read_callback(self, msg: ActuatorReadRequest): # defining Callback for read
        self.get_logger().info("Read Request Msg received")

        par_object = client.get_node(msg.actuator_id)
        state = client.get_node(par_object.get_children()[1])
        
        read_msg = ActuatorRead()
        read_msg.actuator_id = msg.actuator_id
        read_msg.actuator_read_type = msg.actuator_read_type
        
        ## Actuator Read Types
        # Type 1: Single Boolean e.g. Alarm
        # Type 2: int e.g. Tuer

        if msg.actuator_read_type == 1:
            read_msg.actuator_value_bool1 =  state.get_value()
            self.get_logger().info("Read Performed")
            
            self.read_publish.publish(read_msg)
            self.get_logger().info("Read MSG Sent")

        elif msg.actuator_read_type == 2: # Tuer uint16 
            read_msg.actuator_value_int = state.get_value()
            self.get_logger().info("Read Performed")
            
            self.read_publish.publish(read_msg)
            self.get_logger().info("Read MSG Sent")

        else:
            print("GIVEN ACTUATOR READ TYPE NOT KNOWN")

        
def main(args=None):
    rclpy.init(args=args) 

    node = client_node()
    rclpy.spin(node)

    rclpy.shutdown() 
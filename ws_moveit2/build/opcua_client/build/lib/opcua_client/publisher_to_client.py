#!usr/bin/env python3
import rclpy
from rclpy.node import Node
from opcua_interfaces.msg import ActuatorWrite, ActuatorRead, ActuatorReadRequest
import time

class publisher_to_client(Node):

    def __init__(self):
        super().__init__("publisher_to_client")

        ## Connect to Topic
        self.write_publish = self.create_publisher(ActuatorWrite, "Actuator_Write", 10)
        
        self.read_request_publish = self.create_publisher(ActuatorReadRequest, "Actuator_Read_Request", 10)
        
        self.read_receive_subscriber = self.create_subscription(ActuatorRead, "Actuator_Read",
             self.read_receive, 10)
        
        time.sleep(1)
        
        self.get_logger().info("STARTED")
        
        ## WRITE EXAMPLE ##

        ## Actuator Write Types
        # Type 1: Single Boolean e.g. Alarm
        # Type 2: Double Boolean e.g. Tuer

        ## Define MSG Values
        msg_write = ActuatorWrite()
        msg_write.actuator_command_bool1 = False
        #msg_write.actuator_command_bool2 = False
        msg_write.actuator_id = 'ns=4;i=5008'
        msg_write.actuator_write_type = 1

        ## Send Write MSG
        self.write_publish.publish(msg_write)
        self.get_logger().info("MSG SENT")

        ## READ EXAMPLE ##
        
        ## Actuator Read Types
        # Type 1: Single Boolean e.g. Alarm
        # Type 2: int e.g. Tuer
        
        ## Define Read Request
        msg_read_request = ActuatorReadRequest()
        msg_read_request.actuator_id = 'ns=4;i=5008' # Actuator ID
        msg_read_request.actuator_read_type = 1

        ## Send Read Request
        self.read_request_publish.publish(msg_read_request)
        self.get_logger().info("Read MSG Request Sent")

    ## Callback for Read Receiving
    def read_receive(self, msg: ActuatorRead): 
        self.get_logger().info("Read MSG Received")
        
        if msg.actuator_read_type == 1: #Bool
            print("Actuator ID:", msg.actuator_id)
            print("Actuator Read Type:", msg.actuator_read_type)
            print("Actuator Value:", msg.actuator_value_bool1)
        
        elif msg.actuator_read_type == 2: # uint16
            print("Actuator ID:", msg.actuator_id)
            print("Actuator Read Type:", msg.actuator_read_type)
            print("Actuator Value:", msg.actuator_value_int)

        else:
            print("GIVEN ACTUATOR READ TYPE NOT KNOWN")

def main(args=None):
    rclpy.init(args=args) 

    node = publisher_to_client()
    rclpy.spin(node)

    rclpy.shutdown() 
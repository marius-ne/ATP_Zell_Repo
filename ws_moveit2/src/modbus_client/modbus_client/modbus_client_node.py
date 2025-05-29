import rclpy
from rclpy.node import Node
from pymodbus.client import ModbusTcpClient
from pymodbus.exceptions import ConnectionException, ModbusException
from modbus_interfaces.srv import ReadRegister, WriteRegister
import time


class ModbusClientNode(Node):
    def __init__(self):
        super().__init__('modbus_client_node')
        
        self.declare_parameter('modbus_server_host', '192.168.30.20')
        self.declare_parameter('modbus_server_port', 502)
        self.declare_parameter('modbus_slave_id', 65)  # Default slave ID
        self.declare_parameter('poll_interval', 1.0)  # in seconds
        
        self.server_host = self.get_parameter('modbus_server_host').value
        self.server_port = self.get_parameter('modbus_server_port').value
        self.slave_id = self.get_parameter('modbus_slave_id').value
        self.poll_interval = self.get_parameter('poll_interval').value

        self.client = ModbusTcpClient(
            host=self.server_host,
            port=self.server_port
        )
        
        # Connect to Modbus
        try:
            self.connect()
        except ConnectionException as e:
            self.get_logger().error(f'Failed to connect to Modbus server: {e}')
        
        
        #self.timer = self.create_timer(self.poll_interval, self.poll_modbus_data_callback)

        # Service definitions
        self.read_register_service = self.create_service(ReadRegister, 'read_register_service', self.read_register_callback)
        self.write_register_service = self.create_service(WriteRegister, 'write_register_service', self.write_register_callback)

        time.sleep(0.5) # Wait to establish connections

        self.get_logger().info(f'Modbus client node started. Connected to {self.server_host}:{self.server_port}')

    
    def connect(self):
        """Connect to the Modbus server"""
        if not self.client.connect():
            self.get_logger().error('Failed to connect to Modbus server')
            return False
        self.get_logger().info('Connected to Modbus server')
        return True
    
    def disconnect(self):
        """Disconnect from the Modbus server"""
        if self.client.is_socket_open():
            self.client.close()
            self.get_logger().info('Disconnected from Modbus server')
    
    def read_register_callback(self, request, response):
        address = request.address
        count = request.count

        try:
            if not self.client.is_socket_open():
                if not self.connect():
                    response.message = str('Not connected to Modbus server')
                    response.success = False
            
            modbus_response = self.client.read_holding_registers(address, count, slave=self.slave_id)
            if modbus_response.isError():
                self.get_logger().error(f'Error reading holding registers: {modbus_response}')
                response.message = str(modbus_response)
                response.success = False
            
            self.get_logger().debug(f'Read holding registers at address {address}: {modbus_response.registers}')
            response.registers = modbus_response.registers
            response.success = True
            
        except (ConnectionException, ModbusException) as e:
            self.get_logger().error(f'Modbus read error: {e}')
            response.message = str(e)
            response.success = False
    
    def write_register_callback(self, request, response):
        address = request.address
        value = request.value

        try:
            if not self.client.is_socket_open():
                if not self.connect():
                    response.message = str('Not connected to Modbus server')
                    response.success = False
                    
            modbus_response = self.client.write_register(address, value, slave=self.slave_id)
            if modbus_response.isError():
                self.get_logger().error(f'Error writing to register: {modbus_response}')
                response.message = str(modbus_response)
                response.success = False
                
            self.get_logger().debug(f'Wrote value {value} to register at address {address}')
            response.success = True
            
        except (ConnectionException, ModbusException) as e:
            self.get_logger().error(f'Modbus write error: {e}')
            response.message = str(e)
            response.success = False
    
    def poll_modbus_data_callback(self):
        """Periodically poll data from the Modbus server"""
        try:
            read_response= self.client.read_holding_registers(address=1536, count=1, slave=self.slave_id)

            if read_response:
                self.get_logger().info(f'Read registers: {read_response}')
        except Exception as e:
            self.get_logger().error(f'Error during Modbus polling: {e}')


def main(args=None):
    rclpy.init(args=args)
    node = ModbusClientNode()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        # Clean up
        node.disconnect()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

import rclpy
from rclpy.node import Node
from rclpy.parameter import Parameter
from pymodbus.client import ModbusTcpClient
from pymodbus.exceptions import ConnectionException, ModbusException
from modbus_interfaces.srv import ReadRegister, WriteRegister
import time
from ament_index_python.packages import get_package_share_directory
import os
import yaml


class ModbusClientNode(Node):
    def __init__(self):
        super().__init__('modbus_client_node')
        
        self._load_config_file()
        
        # Declare default parameters only if they haven't been declared yet by yaml config file
        if not self.has_parameter('modbus_server_host'):
            self.declare_parameter('modbus_server_host', '192.168.30.20')
        if not self.has_parameter('modbus_server_port'):
            self.declare_parameter('modbus_server_port', 502)
        if not self.has_parameter('modbus_slave_id'):
            self.declare_parameter('modbus_slave_id', 65)  # Default slave ID
        
        self.server_host = self.get_parameter('modbus_server_host').value
        self.server_port = self.get_parameter('modbus_server_port').value
        self.slave_id = self.get_parameter('modbus_slave_id').value

        self.client = ModbusTcpClient(
            host=self.server_host,
            port=self.server_port
        )
        
        # Connect to Modbus
        try:
            self.connect()
        except ConnectionException as e:
            self.get_logger().error(f'Failed to connect to Modbus server: {e}')
        
        
        # Service definitions
        self.read_register_service = self.create_service(ReadRegister, 'read_register_service', self.read_register_callback)
        self.write_register_service = self.create_service(WriteRegister, 'write_register_service', self.write_register_callback)

        time.sleep(0.5) # Wait to establish services

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
        self.get_logger().info(f'Received read request - Address: {request.address}, Count: {request.count}')

        read_address = request.address
        read_count = request.count

        try:
            if not self.client.is_socket_open():
                if not self.connect():
                    response.message = str('Not connected to Modbus server')
                    response.success = False
                    return response
            
            modbus_response = self.client.read_holding_registers(address=read_address, count=read_count, slave=self.slave_id)
            if modbus_response.isError():
                self.get_logger().error(f'Error reading holding registers: {modbus_response}')
                response.message = str(modbus_response)
                response.success = False
            
            self.get_logger().debug(f'Read holding registers at address {read_address}: {modbus_response.registers}')
            response.registers = modbus_response.registers[0]
            response.success = True
            
        except (ConnectionException, ModbusException) as e:
            self.get_logger().error(f'Modbus read error: {e}')
            response.message = str(e)
            response.success = False

        return response
    
    def write_register_callback(self, request, response):
        self.get_logger().info(f'Received write request - Address: {request.address}, Value: {request.value}')

        write_address = request.address
        write_value = request.value

        try:
            if not self.client.is_socket_open():
                if not self.connect():
                    response.message = str('Not connected to Modbus server')
                    response.success = False
                    return response
            modbus_response = self.client.write_register(address=write_address, value=write_value, slave=self.slave_id)
            if modbus_response.isError():
                self.get_logger().error(f'Error writing to register: {modbus_response}')
                response.message = str(modbus_response)
                response.success = False
            
            self.get_logger().info(f'Wrote value {write_value} to register at address {write_address}')
            response.success = True
            
        except (ConnectionException, ModbusException) as e:
            self.get_logger().error(f'Modbus write error: {e}')
            response.message = str(e)
            response.success = False
        
        return response
    
    def poll_modbus_data_callback(self):
        """Periodically poll data from the Modbus server"""
        try:
            read_response= self.client.read_holding_registers(address=1536, count=1, slave=self.slave_id)

            if read_response:
                self.get_logger().info(f'Read registers: {read_response}')
        except Exception as e:
            self.get_logger().error(f'Error during Modbus polling: {e}')

    def _load_config_file(self):
        """Load configuration parameters from a YAML file"""
        try:
            config_file_path = os.path.join(get_package_share_directory('modbus_client'), 'config', 'modbus_config.yaml')
            if os.path.exists(config_file_path):
                with open(config_file_path, 'r') as file:
                    config_data = yaml.safe_load(file)
                    if 'modbus_client_node' in config_data and 'ros__parameters' in config_data['modbus_client_node']:
                        params = config_data['modbus_client_node']['ros__parameters']
                        for param_name, param_value in params.items():
                            self.declare_parameter(param_name, param_value)
                            self.get_logger().info(f'Loaded parameter {param_name}: {param_value}')
                    else:
                        self.get_logger().warn('Invalid YAML structure in config file')
            else:
                self.get_logger().warn(f'Config file not found: {config_file_path}')
        except Exception as e:
            self.get_logger().error(f'Error loading config file: {e}')


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

import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/autopilot/ws/restackcell/ws_moveit2/install/interface_opcua'

import rclpy
from rclpy.node import Node

from std_msgs.msg import Float32
#from client_node_io_link import restackcell_durchfluss

#### Added by wml
from opcua import Client
import struct
import time

def connect_to_opcua_server(url):
    client = Client(url)
    client.connect()
    return client

def read_byte_string(client, node_id):
    node = client.get_node(node_id)
    value = node.get_value()
    return value

def calculate_flow_bemi_1_2(raw_data):
    # Festo Durchflusssensoren SFAH
    # Extrahieren der ersten zwei Bytes (Position 0 und 1)
    relevant_bytes = raw_data[:2]  # Extrahieren der ersten 2 Bytes

    # Interpretieren des Byte-Strings als 16-bit Ganzzahl (Little Endian)
    # Wenn Ihre Daten in Big Endian sind, verwenden Sie '>H' statt '<H'
    value = struct.unpack('>H', relevant_bytes)[0]

    # Anwenden der Umrechnungsfaktoren
    result = value * 0.001220777635 - 10
    # Runden des Ergebnisses auf 3 Nachkommastellen
    flowrate = round(result, 3)
    return flowrate

def calculate_volume_bemi_1_2(raw_data):
    # Festo Durchflusssensoren SFAH
    # Extrahieren der ersten zwei Bytes (Position 0 und 1)
    relevant_bytes = raw_data[2:6]  # Extrahieren der ersten 2 Bytes

    # Interpretieren des Byte-Strings als 16-bit Ganzzahl (Little Endian)
    # Wenn Ihre Daten in Big Endian sind, verwenden Sie '>H' statt '<H'
    value = int.from_bytes(relevant_bytes, byteorder='big', signed=True)

    # Anwenden der Umrechnungsfaktoren
    result = value * 0.000610388818
    # Runden des Ergebnisses auf 3 Nachkommastellen
    flowrate = round(result, 3)
    return flowrate

def get_volume_bemi_2(client, node_id='ns=7;i=694'):
    raw_data = read_byte_string(client, node_id)
    #print(raw_data)
    flowrate = calculate_volume_bemi_1_2(raw_data)
    print(f'Volume Bemi 2: {flowrate}')
    return flowrate

def calculate_flow_spindle(raw_data):
    # Festo Durchflusssensor FSAB
    """
    Berechnet den Durchfluss aus einer gegebenen Bytefolge basierend auf MDC1-Beschreibung:
    Relevante Parameter aus der SFAB Durchflusssensor Dokumentation:
        Unterer Messbereichswert (0x01):
            Wert: 36 (SFAB-600).
            Einheit: Rohdatenwert für den minimalen Messbereich.
        Oberer Messbereichswert (0x02):
            Wert: 3600 (SFAB-600).
            Einheit: Rohdatenwert für den maximalen Messbereich.
        Einheitencode (0x03):
            Wert: 1349, was für m³/h steht.
            Dies muss in l/min umgerechnet werden: 1 m³/h = 16.6667 l/min
        Skalierung (0x04):
            Wert: -2
            Der Skalierungsfaktor zeigt, dass der MDC-Wert um den Faktor 10^(-2) skaliert werden muss.

    :param raw_data: Die Prozessdaten als Bytefolge (mindestens 3 Bytes)
    :return: Der berechnete Durchflusswert in l/min
    """
    if len(raw_data) < 3:
        raise ValueError("Die Bytefolge ist zu kurz, mindestens 3 Bytes erforderlich.")
    # MDC-Wert (16-Bit Durchflusswert)

    mdc_value = int.from_bytes(raw_data[0:2], byteorder='big', signed=True)
    #print(raw_data)
    if mdc_value < 0.0:
        #print(mdc_value," MDC value is smaller than 0.")
        offset = mdc_value
        mdc_value -= offset
    # Skalierungsfaktor (8-Bit Exponent)
    mdc_exponent = int.from_bytes(raw_data[2:3], byteorder='big', signed=True)
    #print("MDC Exponent", mdc_exponent)
    # Umrechnungsfaktor von m³/h in l/min
    # Durchfluss=Rohwert ⋅ 10^(Skalierungsfaktor) ⋅ Umrechnungsfaktor(m³/h → l/min)
    conversion_factor = 16.6667
    # Berechnung des Durchflusswerts
    flowrate = mdc_value * (10 ** mdc_exponent) * conversion_factor
    return flowrate


def calculate_volume_from_client(client, node_id, duration, interval):
    """
    Berechnet das Volumen durch Integration des Durchflusses.
    :param client: Verbundener OPC UA Client.
    :param node_id: Node ID des Durchflusswerts.
    :param duration: Dauer der Messung in Sekunden.
    :param interval: Zeitintervall zwischen Messungen in Sekunden.
    :return: Das berechnete Volumen in Litern.
    """
    total_volume = 0.0
    num_intervals = int(duration / interval)

    for _ in range(num_intervals):
        raw_data = read_byte_string(client, node_id)  # Durchflusswert lesen
        flow_rate = calculate_flow_spindle(raw_data)
        total_volume += flow_rate * interval / 60  # Volumen in Litern addieren
        time.sleep(interval)  # Warten bis zur nächsten Messung
        print(total_volume)

    return total_volume

def calculate_volume_from_flowrate(duration, measured_flowrate, total_volume):
    """
    Berechnet das Volumen durch Integration des Durchflusses.
    :param duration: Dauer der Messung in Sekunden.
    :return: Das berechnete Volumen in Litern.
    """
    total_volume += measured_flowrate * duration / 60  # Volumen in Litern addieren
    return total_volume

def get_flow_rate_spindle(client, node_id='ns=7;i=696'):
    raw_data = read_byte_string(client, node_id)
    flowrate = calculate_flow_spindle(raw_data)
    print(f'Flowrate spindle: {flowrate}')
    return flowrate

def get_flow_rate_bemi_1(client, node_id='ns=7;i=690'):
    raw_data = read_byte_string(client, node_id)
    flowrate = calculate_flow_bemi_1_2(raw_data)
    print(f'Flowrate Bemi 1: {flowrate}')
    return flowrate

def get_flow_rate_bemi_2(client, node_id='ns=7;i=694'):
    raw_data = read_byte_string(client, node_id)
    flowrate = calculate_flow_bemi_1_2(raw_data)
    print(f'Flowrate Bemi 2: {flowrate}')
    return flowrate



class ClientNodeIoLink(Node):

    def __init__(self):
        super().__init__(node_name="client_node_io_link")
        self.publisher_sensor1 = self.create_publisher(Float32, 'Durchfluss_Sensor_Bemi_1', 10)   # Publisher Sensor 1
        self.publisher_sensor2 = self.create_publisher(Float32, 'Durchfluss_Sensor_Bemi_2', 10)   # Publisher Sensor 2
        self.publisher_sensor3 = self.create_publisher(Float32, 'Durchfluss_Sensor_Spindel', 10)  # Publisher Sensor 3
        self.timer_period = 50 # seconds
        self.timer = self.create_timer(self.timer_period, self.timer_callback)
        self.url = 'opc.tcp://192.168.13.179:4841'
        self.client = connect_to_opcua_server(self.url)
        self.volume_sensor1 = 0.0
        self.volume_sensor2 = 0.0
        self.volume_sensor3 = 0.0
        self.get_logger().info('Created OPC UA IO Link Node')

    def timer_callback(self):

        # Sensordaten auslesen     
        flow_rate_bemi_1 = get_flow_rate_bemi_1(self.client)     #Variable von Sensorwert 1
        flow_rate_bemi_2 =  get_flow_rate_bemi_2(self.client)    #Variable von Sensorwert 2
        flow_rate_spindle = get_flow_rate_spindle(self.client)   #Variable von Sensorwert 3

        # Volumen berechnen
        #self.volume_sensor1 += flow_rate_bemi_1 * self.timer / 60    # Differenzvolumen in Litern addieren
        #self.volume_sensor2 += flow_rate_bemi_2 * self.timer / 60
        #self.volume_sensor3 += flow_rate_spindle * self.timer / 60

        # Danach Sensordaten in msg packen
        Msg1 = Float32()
        Msg2 = Float32()
        Msg3 = Float32()
        Msg1.data = flow_rate_bemi_1    # or integrated volume_sensor1
        Msg2.data = flow_rate_bemi_2    # or integrated volume_sensor2
        Msg3.data = flow_rate_spindle   # or integrated volume_sensor3

        # Sensordaten publishen
        self.publisher_sensor1.publish(Msg1)
        self.publisher_sensor2.publish(Msg2)
        self.publisher_sensor3.publish(Msg3)

        # Logoutput, dass Sensordaten gepublished wurden
        self.get_logger().info('Publishing: "%.3f"' % Msg1.data)
        self.get_logger().info('Publishing: "%.3f"' % Msg2.data)
        self.get_logger().info('Publishing: "%.3f"' % Msg3.data)


def main(args=None):
    rclpy.init(args=args)

    node = ClientNodeIoLink()

    rclpy.spin(node)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    # node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()


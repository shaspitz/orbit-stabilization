'''
Created on May 7, 2020

@author: shawn
'''
import struct
import serial as ser
import time

# Serial configuration
ser = ser.Serial(port='COM5', baudrate=115200, parity='N')
if ser.is_open:
    ser.close()
    ser.open()
else:
    ser.open()


class psoc_interface:

    def __init__(self, ser):
        self.ser = ser

    def start_psoc(self):
        '''
        Constructs and sends packet containing command to start psoc timer
        and activate other commands
        '''
        command = 2
        packet_size = 2

        # Transmit byte array
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        self.ser.write(transmit_packet)

    def send_sim_env_info(self, Ts, Kinf, Finf):
        '''
        Initializes psoc interface with parameters for
        simulation, estimation and control
        '''
        return 0

    def request_input(self):
        '''
        Receives two double precision floats from PSOC
        (for getting inputs)
        '''
        command = 3
        packet_size = 2

        # Transmit byte array
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        self.ser.write(transmit_packet)

        packet_size = int.from_bytes(self.ser.read(), byteorder='little')

        command = int.from_bytes(ser.read(), byteorder='little')
        if command == 3 and packet_size == 18:

            buffer = ser.read(packet_size-2)
            input_1 = struct.unpack('d', buffer[:8])[0]
            input_2 = struct.unpack('d', buffer[8:])[0]

            return input_1, input_2
        else:
            print('Error!')

    def relay_double(self, double):
        '''
        Sends and receives a double to and from psoc
        (for testing, currently doesn't work with other functions)
        '''
        command = 1
        buffer = struct.pack('d', double)
        packet_size = len(buffer) + 2

        # Transmit byte array
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        transmit_packet += buffer
        ser.write(transmit_packet)

        # Receive byte array
        packet_size = int.from_bytes(ser.read(), byteorder='little')
        command = int.from_bytes(ser.read(), byteorder='little')
        if command == 1 and packet_size == 10:
            buffer = ser.read(packet_size-2)
            double = struct.unpack('d', buffer)[0]

            return double
        else:
            print('Error!')


# testing
psoc = psoc_interface(ser)

# test_double = psoc.relay_double(1.234567)
# print(test_double)

psoc.start_psoc()
input_1, input_2 = psoc.request_input()
print(input_1, input_2)



'''
Created on May 7, 2020

@author: shawn
'''
import struct
import serial as ser
import time
import numpy as np

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

    def send_sim_env_info(self, Kinf, Ts=None, Finf=None):
        '''
        Initializes psoc interface with parameters for
        simulation, estimation and control
        Ts   -> scalar
        Kinf -> 4x4 array
        Finf -> 2x4 array
        '''
        command = 2
        # Add Ts and Finf to packet later
#         buffer = bytes([Ts])

        '''
        implement embedded for loops here to load buffer
        with all the floats from Kinf anf Finf. 
        If this is too many bytes at once, might need to split up
        into separate functions.
        '''
        buffer = bytes()
        for x in range(len(Kinf)):
            for y in range(len(Kinf[0])):
                print('component of Kinf: ', Kinf[x][y])
                print('bytes: ', struct.pack('d', Kinf[x][y]), 'len: ', len(struct.pack('d', Kinf[x][y])))
                buffer += struct.pack('d', Kinf[x][y])

        print('TEST', struct.unpack('d', buffer[-8:]))
        print('TEST', struct.unpack('d', buffer[120:]))

        packet_size = len(buffer)+2

        # Transmit byte array
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        transmit_packet += buffer
        ser.write(transmit_packet)

        return 0

    def start_psoc(self):
        '''
        Constructs and sends packet containing command to start psoc timer
        and activate other commands
        '''
        command = 3
        packet_size = 2

        # Transmit byte array
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        self.ser.write(transmit_packet)

        # Receive relayed byte array and confirm psoc started
        packet_size = int.from_bytes(self.ser.read(), byteorder='little')
        command = int.from_bytes(ser.read(), byteorder='little')

        if packet_size == 2 and command == 3:
            print('psoc timing started!')

    def request_input(self):
        '''
        Receives two double precision floats from PSOC
        (for getting inputs)
        '''
        command = 4
        packet_size = 2

        # Transmit byte array
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        self.ser.write(transmit_packet)

        packet_size = int.from_bytes(self.ser.read(), byteorder='little')

        command = int.from_bytes(self.ser.read(), byteorder='little')

        if command == 4 and packet_size == 18:

            # Receive byte array
            buffer = ser.read(packet_size-2)
            input_1 = struct.unpack('d', buffer[:8])[0]
            input_2 = struct.unpack('d', buffer[8:])[0]

            return input_1, input_2
        else:
            print('Error! Printing incorrect command or packet size.')
            print('Command:', command, 'Packet size:', packet_size)


# testing
psoc = psoc_interface(ser)

# test_double = psoc.relay_double(1.234567)
# print(test_double)

psoc.send_sim_env_info(np.array([[1.0, 1.0, 1.0, 1.0],
                                 [1.0, 1.0, 1.0, 1.0],
                                 [1.0, 1.0, 1.0, 1.0],
                                 [1.0, 1.0, 1.0, 9.34267]]))
psoc.start_psoc()
input_1, input_2 = psoc.request_input()
print(input_1, input_2)

input_1, input_2 = psoc.request_input()
print(input_1, input_2)

# psoc_interface.send_sim_env_info(1, 5.6*np.ones((4, 4)))



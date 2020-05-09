'''
Created on May 7, 2020

@author: shawn
'''
import struct
import serial as ser
import time
import numpy as np


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
        self.ser.write(transmit_packet)

        # Receive byte array
        packet_size = int.from_bytes(self.ser.read(), byteorder='little')
        command = int.from_bytes(self.ser.read(), byteorder='little')
        if command == 1 and packet_size == 10:
            buffer = self.ser.read(packet_size-2)
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
        # Construct packet containing Kinf
        command = 2

        buffer = bytes()
        for row in range(len(Kinf)):
            for col in range(len(Kinf[0])):
                buffer += struct.pack('d', Kinf[row][col])

        packet_size = len(buffer)+2

        # Transmit packet for Kinf
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        transmit_packet += buffer
        self.ser.write(transmit_packet)

        # Construct packet containing Ts and Finf
        command = 3

        buffer = bytes([int(Ts)])
        for row in range(len(Finf)):
            for col in range(len(Finf[0])):
                buffer += struct.pack('d', Finf[row][col])

        packet_size = len(buffer)+2

        # Transmit packet for Ts and Finf
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        transmit_packet += buffer
        self.ser.write(transmit_packet)

    def start_psoc(self):
        '''
        Constructs and sends packet containing command to start psoc timer
        and activate flag enabling all other commands
        '''
        command = 4
        packet_size = 2

        # Transmit byte array
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        self.ser.write(transmit_packet)

        # Receive relayed byte array and confirm psoc started
        packet_size_return = int.from_bytes(self.ser.read(), byteorder='little')
        command_return = int.from_bytes(self.ser.read(), byteorder='little')

        if packet_size_return == packet_size and command_return == command:
            print('psoc timing started')

    def request_input(self):
        '''
        Receives two double precision floats from PSOC
        (for getting inputs)
        '''
        command = 5
        packet_size = 2

        # Transmit byte array with command
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        self.ser.write(transmit_packet)

        # Receive byte array with inputs
        packet_size_return = int.from_bytes(self.ser.read(), byteorder='little')
        command_return = int.from_bytes(self.ser.read(), byteorder='little')

        if packet_size_return == packet_size+16 and command_return == command:
            buffer = self.ser.read(packet_size_return-2)
            input_1 = struct.unpack('d', buffer[:8])[0]
            input_2 = struct.unpack('d', buffer[8:])[0]

            return input_1, input_2
        else:
            print('Error! Printing incorrect command or packet size.')
            print('Command:', command_return, 'Packet size:', packet_size_return)

    def send_measurement(self, meas):
        '''
        Sends current measurement of the satellite state to psoc
        Note that input is a 2d numpy array
        '''
        command = 6

        buffer = bytes()
        for state in range(len(meas)):
            buffer += struct.pack('d', meas[state][0])

        packet_size = len(buffer)+2

        # Transmit packet with measurement
        transmit_packet = bytes([packet_size])
        transmit_packet += bytes([command])
        transmit_packet += buffer
        self.ser.write(transmit_packet)

        # Receive byte array confirming measurement was obtained
        packet_size_return = int.from_bytes(self.ser.read(), byteorder='little')
        command_return = int.from_bytes(self.ser.read(), byteorder='little')

        if packet_size_return == 2 and command_return == command:
            print('Measurement processed by psoc')
        else:
            print('Error! Printing incorrect command or packet size.')
            print('Command:', command_return, 'Packet size:', packet_size_return)

# testing

# Serial configuration
ser = ser.Serial(port='COM5', baudrate=115200, parity='N')
if ser.is_open:
    ser.close()
    ser.open()
else:
    ser.open()

psoc = psoc_interface(ser)

# test_double = psoc.relay_double(1.234567)
# print(test_double)

psoc.send_sim_env_info(Kinf=np.array([[1.0, 2.0, 3.0, 4.0],
                                      [5.0, 6.0, 7.0, 8.0],
                                      [9.0, 10.0, 11.0, 12.0],
                                      [13.0, 14.0, 15.0, 16.0]]),
                                      Ts=5,
                                      Finf=np.array([[1.0, 2.0, 3.0, 4.0],
                                                     [5.0, 6.0, 7.0, 8.0]]))
psoc.start_psoc()

input_1, input_2 = psoc.request_input()
print(input_1, input_2)

psoc.send_measurement(np.array([[50.2],
                                [5.234625],
                                [42.63],
                                [42.63]]))

input_1, input_2 = psoc.request_input()
print(input_1, input_2)

input_1, input_2 = psoc.request_input()
print(input_1, input_2)

Finf=np.array([[1.0, 2.0, 3.0, 4.0],
               [5.0, 6.0, 7.0, 8.0]])

x_est = np.array([[50.2],
          [5.234625],
          [42.63],
          [42.63]])

print(-Finf @ x_est)


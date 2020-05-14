'''
Created on May 14, 2020

@author: Shawn Marshall-Spitzbart

Contains the Psoc_interface class
'''
import struct


class Psoc_interface:
    '''
    Class for communicating with psoc micrcontroller
    '''
    def __init__(self, ser):
        self.ser = ser

    def relay_double(self, double):
        '''
        Sends and receives a double to and from psoc
        (for testing)
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

    def send_sim_env_info(self, Kinf, Finf, Ts=None):
        '''
        Initializes psoc interface with parameters for
        simulation_main, estimation and control
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

        # Receive relayed byte array and confirm Kinf was receieved
        packet_size_return = int.from_bytes(self.ser.read(), byteorder='little')
        command_return = int.from_bytes(self.ser.read(), byteorder='little')

        if packet_size_return == 2 and command_return == command:
            print('Kinf received')

        # Construct packet containing Ts and Finf
        command = 3

        if Ts is None:
            Ts = 1

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

        # Receive relayed byte array and confirm Ts and Finf were receieved
        packet_size_return = int.from_bytes(self.ser.read(), byteorder='little')
        command_return = int.from_bytes(self.ser.read(), byteorder='little')

        if packet_size_return == 2 and command_return == command:
            print('Ts and Finf received')

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

        elif packet_size_return == packet_size and command_return == 44:
            print('psoc timing already started, possible error')

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
        packet_size_return = int.from_bytes(self.ser.read(),
                                            byteorder='little')
        command_return = int.from_bytes(self.ser.read(), byteorder='little')

        if packet_size_return == packet_size+20 and command_return == command:
            buffer = self.ser.read(packet_size_return-2)
            input_1 = struct.unpack('d', buffer[:8])[0]
            input_2 = struct.unpack('d', buffer[8:16])[0]
            psoc_time = struct.unpack('I', buffer[16:20])[0]

            return input_1, input_2, psoc_time
        else:
            print('Error! Printing incorrect command or packet size.')
            print('Command:', command_return, 'Packet size:',
                  packet_size_return)

    def send_measurement(self, meas):
        '''
        Sends current measurement of the satellite state to psoc
        Note that input is a 1d numpy array
        '''
        command = 6

        buffer = bytes()
        for state in range(len(meas)):
            buffer += struct.pack('d', meas[state])

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
            print('Command:', command_return, 'Packet size:',
                  packet_size_return)

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


def send_double_packet(command, double):
    '''
    Constructs and sends packet containing double (with command)
    '''
    buffer = struct.pack('d', double)
    packet_size = len(buffer) + 2

    # Transmit byte array
    transmit_packet = bytes([packet_size])
    transmit_packet += bytes([command])
    transmit_packet += buffer

    ser.write(transmit_packet)


def send_command(command):
    '''
    Constructs and sends packet containing command only
    '''
    packet_size = 2

    # Transmit byte array
    transmit_packet = bytes([packet_size])
    transmit_packet += bytes([command])

    ser.write(transmit_packet)


def read_double_packet():
    '''
    Receives double precision float from PSOC (with command)
    '''
    packet_size = int.from_bytes(ser.read(), byteorder='little')
    command = int.from_bytes(ser.read(), byteorder='little')
    buffer = ser.read(packet_size-2)
    double = struct.unpack('d', buffer)[0]

    return command, double


def read_two_double_packet():
    '''
    Receives two double precision floats from PSOC (with command)
    (for getting input commands)
    '''
    packet_size = int.from_bytes(ser.read(), byteorder='little')
    print('return packet size: ', packet_size)
    command = int.from_bytes(ser.read(), byteorder='little')
    buffer = ser.read(packet_size-2)
    print('buffer: ', buffer)
    double_1 = struct.unpack('d', buffer[:8])[0]
    double_2 = struct.unpack('d', buffer[8:])[0]

    return command, double_1, double_2


# Testing
# send_double_packet(command=1, double=563434534534.2424234)
# return_command, rx_double = read_double_packet()
# print(rx_double)

# Activate PSOC
send_command(2)

# Get inputs
for i in range(5):
    send_command(3)
    command, double_1, double_2 = read_two_double_packet()
    print('return command:', command, 'doubles:', double_1, double_2)
    time.sleep(1)


'''
Created on May 7, 2020

@author: shawn
'''
import struct
import serial as ser

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


def read_double_packet():
    '''
    Receives double precision float from PSOC (with command)
    '''
    packet_size = int.from_bytes(ser.read(), byteorder='little')
    command = int.from_bytes(ser.read(), byteorder='little')
    buffer = ser.read(packet_size-2)
    double = struct.unpack('d', buffer)[0]

    return command, double


# Testing
send_double_packet(5, 563434534534.2424234)
return_command, rx_double = read_double_packet()

print(rx_double)
print('If this prints, full packet received!!!! You are not stupid')

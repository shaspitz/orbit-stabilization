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


# def send_double_packet(command, double):
#     '''
#     Constructs packet
#     '''
#     buffer = struct.pack('d', double)
#     packet_size = len(buffer) + 2
#
#     transmit_packet = bytes([packet_size])
#     transmit_packet += bytes([command])

# Pack float
send_float = 5353535355324.42342
num = struct.pack('f', send_float)
packet = bytes([6])
packet += bytes([5])
packet += num
print('bytes in sending packet: ', len(packet))
print('packet being sent: ', packet)

ser.write(packet)
print('packet was sent')
packet_size = int.from_bytes(ser.read(), byteorder='little')
print('returned packet size:', packet_size)
command = int.from_bytes(ser.read(), byteorder='little')
print('returned command:', command)
buffer = ser.read(packet_size-2)
print('bytes buffer: ', buffer)
return_float = struct.unpack('f', buffer)[0]
print('returned float', return_float)

print('If this prints, full packet received!!!! You are not stupid')

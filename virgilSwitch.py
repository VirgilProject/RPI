#!/usr/bin/python
import os, sys
import smbus

bus = smbus.SMBus(1)

DEVICE_ADDRESS = 0x4d

def writeI2CToSwitch(IO):
    bus.write_byte_data(DEVICE_ADDRESS,0x00,IO)

if __name__ == '__main__':
    address = int(sys.argv[1],16)
    writeI2CToSwitch(address)


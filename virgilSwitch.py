#!/usr/bin/python
import os, sys
import smbus

bus = smbus.SMBus(1)

def writeI2CToSwitch(IO,DEVICE_ADDRESS):
    bus.write_byte_data(DEVICE_ADDRESS,0x00,IO)

if __name__ == '__main__':
    address = int(sys.argv[1],16)
    device = int(sys.argv[2],16)
    writeI2CToSwitch(address,device)


#! /usr/bin/env python3
#sudo pip3 install pyserial

#Usage: ./read.py > file.txt
#В файле заменить ' \r \n \b

import serial
ser = serial.Serial('/dev/ttyUSB0', baudrate=115200)
while (1):
	print(ser.read())

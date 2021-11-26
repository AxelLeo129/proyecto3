#!/usr/bin/env python

import time
from bmp280 import BMP280

try:
    from smbus2 import SMBus
except ImportError:
    from smbus import SMBus

# Initialise the BMP280
bus = SMBus(1)
bmp280 = BMP280(i2c_dev=bus)

while True:
    data_temperature = ''
    data_pressure = ''
    for i in range(100):
        temperature = bmp280.get_temperature()
        pressure = bmp280.get_pressure()
        data_temperature = data_temperature + '{:05.2f}\n'.format(temperature)
        data_pressure = data_pressure + '{:05.2f}\n'.format(pressure)
        print("Leyendo datos...")
        with open('datos_temperatura.txt', 'w') as file:
            file.write(data_temperature)
        with open('datos_presion.txt', 'w') as file:
            file.write(data_pressure)
        time.sleep(1)
    time.sleep(15)

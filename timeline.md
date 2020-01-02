# smartsolar timeline

## 27/12/2019
We bought the following: 
- Temperature Sensor - Waterproof (DS18B20)
- Jumper Wires 15cm Female to Male - Pack of 10 Red
- Breadboard Mini - White
- Resistor Basic Kit - 100pcs

## 28/12/2019
We conected the DS18B20 to the raspberry pi, following the instractions on http://www.circuitbasics.com/raspberry-pi-ds18b20-temperature-sensor-tutorial/ and ran a c program, we found on https://www.raspberrypi.org/forums/viewtopic.php?t=70709, to read the sensor readings. We made some changes to the c program so that it converts the readings of the sensor, which are in character mode, into actual numbers: [temp.c](../blob/master/code/temp.c)

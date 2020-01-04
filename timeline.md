# smartsolar timeline

## 27/12/2019
We bought the following: 
- Temperature Sensor - Waterproof (DS18B20)
- Jumper Wires 15cm Female to Male - Pack of 10 Red
- Breadboard Mini - White
- Resistor Basic Kit - 100pcs

## 28/12/2019
- We conected the DS18B20 to the raspberry pi, following the instractions on http://www.circuitbasics.com/raspberry-pi-ds18b20-temperature-sensor-tutorial/. 
- Then we wrote a C program, based on https://www.raspberrypi.org/forums/viewtopic.php?t=70709, to read the sensor readings. 
- We made some changes to the C program so that it converts the readings of the sensor, which are in character mode, into actual numbers. The source code can be seen [here](../master/code/temp.c)
- This is a screenshot of the program output while running:
![alt text](https://github.com/protogelrafinas/smartsolar/blob/master/photos/1st_prog_prtsc.png "hahah")

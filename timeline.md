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
![alt text](https://github.com/protogelrafinas/smartsolar/blob/master/photos/1st_prog_prtsc.png "PrtSc taken on the raspberry pi")

## 6/1/2020
- To send the sensor's readings from the raspberry pi to another device we are using the [mqtt protocol](https://mqtt.org), wich is a protocol that makes communication between devices through network easier.
- We installed the following mqtt implementations for raspberry pi:
  - the mosquito broker, by typing in the terminal: `sudo apt install mosquitto`.
  - and the mosquito clients, by typing in the terminal: `sudo apt-get install mosquitto-clients`.
- Then we wrote a C program which publishes the sensor's readings to the broker. The source code can be seen [here](../master/code/temp_mqtt.c).
- Now the raspberry pi can send the sensor's readings to other devices through network. Here is a screenshot of an other computer, in wich we have installed the mosquitto clients, receiving the sensor's readings: ![alt text](https://github.com/protogelrafinas/smartsolar/blob/master/photos/mqtt_receive.png "PrtSc taken on an other computer")

The command `mosquitto_sub -h 192.168.1.14 -t temp` subscribes to the raspberry pi (ip = 192.168.1.14) and reads the the temperature from the mqtt topic "temp".

## 2/2/2020
We installed the sensor in the solar heater using some silicon to secure it in place. The sensor was placed inside of a thermowell as you can see in the following picture: ![alt text](https://github.com/protogelrafinas/smartsolar/blob/master/photos/IMG_20200202_170847.jpg "photo taken while istalling the sensor")

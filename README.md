# Food Collector - Merino

Implementation of Computer Graphics and Multimedia "food collection" project. We develop a project devoted to the creation of a "food collection" 3D videogame.

# Install necessary libraries

## Install the OpenGL library
Install the OpenGL library runing the following commands as `root`:
```
apt-get update
apt-get install freeglut3-dev
```

## Install the JPEG library
Download this library from: http://www.ijg.org/

Once you downloaded the library extract it, enter to the `jpeg-9b` folder and run the following commands as `root`:
```
./configure
make
make test
make install
ranlib /usr/local/lib/libjpeg.a
ldconfig /usr/local/lib
```

# Download the project

To get the project you should download the project from this link:
https://github.com/pestomerdes/food_collector/archive/master.zip

# Compile and execute the game
Compile the game using the Makefile on the root folder of the project and run this command:
```
make
```
When the game is compiled you can start to play the game and enjoy a good time. To run the game execute the command:
```
./food_collector
```
If you want to see more information about the parameters of the program use the next command:
```
./food_collector -h
```
# Arduino setup
In order to run the game using the Arduino game controller you need to install the Arduino IDE and the following libraries:

- Arduino IDE : https://www.arduino.cc/en/Main/Software
- Adafruit Sensor: https://github.com/adafruit/Adafruit_Sensor
- Adafruit ADXL345: https://github.com/adafruit/Adafruit_ADXL345
- DHT sensor library: https://github.com/adafruit/DHT-sensor-library

## Arduino connections
The next step is to connect all the sensors to the Arduino board following the next specifications:
![tag](https://raw.githubusercontent.com/pestomerdes/food_collector/master/Images/arduino_connections.PNG)

Once you have prepared the Arduino environment you can upload the arduino sketch available on the `BGC-sketch` folder of the project on the arduino. Then when you execute the game, if the game detect the arduino, you will be able to play with the Biometrical Game Controller. See game information to more information about the arduino parameters in the game.
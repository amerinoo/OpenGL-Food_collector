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

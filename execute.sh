#!/bin/bash
#sudo usermod -a -G dialout $USER # Needed to execute without sudo
ls /dev/ | grep ttyACM
make
./food_collector

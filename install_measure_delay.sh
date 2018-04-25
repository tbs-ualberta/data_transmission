#!/bin/sh

sudo rm -rf build
mkdir build
cd build
sudo cmake ../src/measure_delay
sudo make
sudo make install

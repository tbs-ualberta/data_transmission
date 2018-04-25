#!/bin/sh

sudo rm -rf build
mkdir build
cd build
sudo cmake ../src/data_transmission
sudo make
sudo make install

#!/bin/sh
sudo rm -rf build
mkdir build
cd build
sudo cmake ..
sudo make
sudo make install

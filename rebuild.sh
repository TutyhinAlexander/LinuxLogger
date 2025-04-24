#!/bin/bash 
#This script will rebuild Logger library and examples

clear

#build
sudo rm -rf build
mkdir build 
cd build
$echo pwd
echo "prepare make configs..."
cmake ..
echo "build project..."
make
echo "install library..."
sudo make install

echo "build examples..."
cd ../examples
sudo rm -rf build
mkdir build
cd build
$echo pwd
cmake ..
make

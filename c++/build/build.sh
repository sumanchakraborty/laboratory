#!/bin/bash

# first argument is the source
echo "building project \"$1\""

echo "rm -rf $1"
rm -rf $1

echo "g++ -g -o $1 $1.cpp -lpcap"
# g++ -g -o $1 $1.cpp -lpcap -lpthread
g++ -Wall -g -o $1 $1.cpp


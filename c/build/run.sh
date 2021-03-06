#!/bin/bash

# first argument is the source
echo "building project ... \"$1\""

echo "rm -rf $1"
rm -rf $1

echo "gcc -g -o $1 $1.c -lpcap"
# gcc -g -o $1 $1.c -lpcap -lpthread
gcc -Wall -g -o $1 $1.c

echo "considering input ... \"$1.in\""
cat $1.in; 

echo "running project ... \"$1\""
./$1 < $1.in


#!/bin/bash
make
./xor
gcc -o export_xor_c export_xor.c -lm
./export_xor_c 0 0
./export_xor_c 1 0
./export_xor_c 0 1
./export_xor_c 1 1
echo ""
./export_xor.py 0 0
./export_xor.py 1 0
./export_xor.py 0 1
./export_xor.py 1 1
exit

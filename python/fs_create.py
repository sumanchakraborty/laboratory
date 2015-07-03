#!/usr/bin/python

import os
import sys
import platform
import math

# File system  Distribution
# -------------------------
# 1KB,25
# 16KB,20
# 128KB,17
# 512KB,17
# 1MB,10
# 8MB,5
# 16MB,5
# 32MB,1
#                   1MB
#          128KB ----+--- 16M
#     16KB --+- 512KB  8MB + 32MB
#  1KB -|
# 

content = "dummy"
contentLength = len(content)

# file system distribution
distribN = ['1KB', '16KB', '128KB', '512KB', '1MB', '8MB', '16MB', '32MB']
distribS = [1, 16, 128, 512, 1024, 8192, 16384, 32768]
distribP = [25, 20, 17, 17, 10, 5, 5, 1]
distribL = len(distribN)

def createNode( start, end ):

   if start > end:
       return
   else:
       index = ( start + end ) / 2

   nameD = "d" + distribN[index]
   nameF = "f" + distribN[index]
   size = distribS[index] * 1024
   perc = distribP[index]

   os.mkdir(nameD)
   os.chdir(nameD)
   for count in range(0, perc):
       name = nameF + str(count)
       block = size / contentLength
       remdr = size % contentLength
       file = open(name, 'w+')
       for blockIndex in range(0, block):
           file.write(content)
       for remdrIndex in range(0, remdr):
           file.write("X")
       file.close()

   createNode( start, ( index - 1 ))
   createNode( ( index + 1 ), end)

   os.chdir(os.pardir)
   return 0

# main

print "------------"
print "Distribution"
print "------------"
print distribN
print distribP

createNode( 0, ( distribL - 1 ))


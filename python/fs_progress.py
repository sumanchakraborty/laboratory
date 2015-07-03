#!/usr/bin/python

import os
import sys
import platform
import math
import time

def progress(end_val, bar_length=20):
    for i in xrange(0, end_val):
        percent = float(i) / end_val
        hashes = '#' * int(round(percent * bar_length))
        spaces = ' ' * (bar_length - len(hashes))
        sys.stdout.write("\rPercent: [{0}] {1}%".format(hashes + spaces, int(round(percent * 100))))
        sys.stdout.flush()


index = 0
for index in xrange(0, 100):
    time.sleep(0.2)
    progress(index)

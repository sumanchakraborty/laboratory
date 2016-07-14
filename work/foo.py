#!/usr/bin/python

import os
import sys
import platform
import time
import psutil as pu
import json
# import tabulate

'''
# print pu.cpu_percent(percpu=True)
for p in pu.process_iter():
        data = p.as_dict(['name',
#                         'pid',
                          'memory_info',
                          'cpu_times',
                          'cpu_percent',
                          'memory_percent'])
'''

row = ''
for p in pu.process_iter():
    head = 'name: '
    row += p.name() + ': '

    this = p.cpu_percent()
    head += 'cp, '
    row += str(this) + ', '

    this = p.cpu_times()
    for field in this._fields:
        head += 'ct:' + field + ', '
        row += str(getattr(this, field)) + ', '

    this = p.memory_percent()
    head += 'mp, '
    row += str(this) + ', '

    this = p.memory_info()
    for field in this._fields:
        head += 'mi:' + field + ', '
        row += str(getattr(this, field)) + ', '

    row += '\n'

print head
print row

'''
print data
dict_to_csv(data, 'foo.csv')
os.system('cat foo.csv')
'''



import os
from xml.etree.ElementTree import iterparse

XML = 'tmp.xml'
FOLDER = 'D'
FILE = 'F'
NAME = 'N'
SIZE = 'L'

content = "workload content"
contentLength = len(content)

for (event, elem) in iterparse(XML, ['start', 'end', 'start-ns', 'end-ns']):
    if event == 'end':
        if elem.tag == FOLDER:
            os.chdir(os.pardir)
    if event == 'start':
        print "working for ...", elem.attrib[NAME]
        if elem.tag == FILE:
            size = int(elem.attrib[SIZE])
            block = size / contentLength
            remdr = size % contentLength
            file = open(elem.attrib[NAME], 'a')
            for blockIndex in range(0, block):
                file.write(content)
            for remdrIndex in range(0, remdr):
                file.write("X")
            file.close()
        if elem.tag == FOLDER:
            os.mkdir(elem.attrib[NAME])
            os.chdir(elem.attrib[NAME])


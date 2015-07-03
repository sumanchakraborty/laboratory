
import os
import sys
import errno
import shutil
from xml.etree.ElementTree import iterparse

XML = 'foo.xml'
LOG_SETUP = "setup.log"

ROOT = 'R'
FOLDER = 'D'
FILE = 'F'
NAME = 'N'
SIZE = 'L'

content = "workload content"
contentLength = len(content)

class logger(object):
    def __init__(self):
        self.terminal = sys.stdout
        self.log = open(LOG_SETUP, "a")

    def write(self, message):
        self.terminal.write(message)
        self.log.write(message)  

def unpack( xml ):
    for (event, elem) in iterparse(xml, ['start', 'end', 'start-ns', 'end-ns']):
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
            if elem.tag == ROOT:
                shutil.rmtree(elem.attrib[NAME], ignore_errors=True)
                os.mkdir(elem.attrib[NAME])
                os.chdir(elem.attrib[NAME])
    return 0;

sys.stderr = logger()
unpack(XML)


#!/usr/bin/python

import os
import sys
import platform

from stat import *
from xml.sax.saxutils import quoteattr as xml_quoteattr

PATH = os.getcwd()
START = "["
STOP  = "]"
SEPARATOR = ":"

def quit():
    print "Usage: xml/crawl/parse"
    exit()

def xml(path):
    result = '<D N=%s>' % xml_quoteattr(os.path.basename(path))
    for item in os.listdir(path):
        itempath = os.path.join(path, item)
        if os.path.isdir(itempath):
            os.chdir(itempath)
            result += xml(os.path.join(path, item))
        elif os.path.isfile(itempath):
            stat = os.stat(item)
            result += '<F N=%s ' % xml_quoteattr(item)
            result += 'L=%s/>' % xml_quoteattr(str(stat[ST_SIZE]))
    result += '</D>'
    os.chdir(os.pardir)
    return result

def crawl(path, result):
    result += START + "D" + SEPARATOR
    result += "%s" % os.path.basename(path)
    result += SEPARATOR
    path = os.path.abspath(path)
    for item in os.listdir(path):
        itempath = os.path.join(path, item)
        if os.path.isdir(itempath):
            os.chdir(itempath)
            result = crawl(itempath, result)
        if os.path.isfile(itempath):
            stat = os.stat(item)
            result += START + "F" + SEPARATOR
            result += "%s" % item
            result += SEPARATOR
            result += str(stat[ST_SIZE])
            result += STOP
    result += STOP
    os.chdir(os.pardir)
    return result

if __name__ == '__main__':

    if len(sys.argv) == 1:
        quit()

    OPT = sys.argv[1]
    if OPT == "xml":
        print xml(PATH)
    elif OPT == "crawl":
        print crawl(PATH, "")
    else:
        quit()


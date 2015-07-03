#!/usr/bin/python

import os
import xml.etree.cElementTree as ET
from xml.etree.ElementTree import iterparse

XML_IN = 'in.xml'
XML_OUT = 'foo.xml'
PACKET = 'Packet'
NAME = 'Name'
VALUE = 'Value'
FILE = 'file'
FOLDER = 'folder'

# object[type, name, length]
def add(root, object):
    for child in root:
        if child.attrib['N'] == object[1]:
            return child
    if object[0] == FILE:
        node = ET.SubElement(root, "F")
        node.set("N", object[1])
        node.set("L", object[2])
    else:
        node = ET.SubElement(root, "D")
        node.set("N", object[1])
    return node

def create(root, name):
    if root:
        return root
    else:
        root = ET.Element("R")
        root.set("N", name)
    return root

def parse( root, xml ):
    isTarget = 0
    isType = 0
    isSize = 0
    node = root
    object = []
    lastObject = []
    for (event, elem) in iterparse(xml, ['start', 'end', 'start-ns', 'end-ns']):
        if event == 'end' and elem.tag == PACKET:
            print lastObject
            node = add(node, lastObject)
            lastObject[:] = []
        if event == 'start':
            for name, value in elem.items():
                if name == VALUE:
                    if isType:
                        isType = 0
                        lastObject.insert(0, value) 
                    if isTarget:
                        isTarget = 0
                        tokens = value.split("\\\\")
                        for index in range(0, len(tokens)):
#                           print (index, tokens[index])
                            if index == 0:
                                root = create(root, tokens[index])
                                node = root
                            elif index == len(tokens) - 1:
                                lastObject.insert(1, tokens[index]) 
                            else:
                                object = ["D", tokens[index], "0"]
                                node = add(node, object)
                    if isSize:
                        isSize = 0
                        lastObject.insert(2, value) 

                if name == NAME:
                    if value == 'target':
                        isTarget = 1
                    if value == 'type':
                        isType = 1
                    if value == 'size':
                        isSize = 1
    return root

# root = create(0, "foo")
# obj = ["D", "0", "dir"]
# dir = add(root, obj)
# obj = ["F", "5", "file"]
# node = add(dir, obj)

root  = parse(0, XML_IN)

tree = ET.ElementTree(root)
tree.write(XML_OUT)


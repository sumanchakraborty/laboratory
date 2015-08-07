#!/usr/bin/python

import re
import string
import argparse

FILE="foo"

def get_file(name):
    foo=open(name, "r")
    lines = foo.read()
    foo.close()
    return lines

def set_file(name, lines):
    foo=open(name, "w")
    foo.write(lines)
    foo.close()

parser = argparse.ArgumentParser(description='Description of your program')
parser.add_argument('-ip', dest='ip', help='IP Address', required=True)
parser.add_argument('-mask', dest='mask', help='Netmask', required=False)
parser.add_argument('-gw', dest='gw', help='Gateway', required=False)
parser.add_argument('-static', dest='static', help='Static/DHCP', required=False)
parser.add_argument('-dns', dest='dns', help='DNS', required=False, action='append')

args = parser.parse_args()

# IP Address
if args.ip: 
    print "IP Address" + " " + args.ip
    old = get_file(FILE)
    new = re.sub("IPADDR=.*", "IPADDR=%s" % args.ip, old)
    set_file(FILE, new)

# Mask
if args.mask: 
    print args.mask

# Gateway
if args.gw: 
    print args.gw

# Static/DHCP
if args.static: 
    print args.static

# DNS
if args.dns: 
    print args.dns


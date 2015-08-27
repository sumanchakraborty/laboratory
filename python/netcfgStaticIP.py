#!/usr/bin/python

import re
import os
import sys
import string
import socket
import argparse

# configuration files
# -------------------
# iface - dhcp, ip, mask, network
# network - hostname, gateway
# dns - dns
file_iface="/etc/sysconfig/network-scripts/ifcfg-eth0"
file_network="/etc/sysconfig/network"
file_dns="/etc/resolv.conf"

parser = argparse.ArgumentParser(description='Description of your program')

parser.add_argument('-iface', dest='iface', help='Interface', required=True)
parser.add_argument('-dhcp', dest='dhcp', help='DHCP/Static', action='store_true')
parser.add_argument('-ip', dest='ip', help='IP Address', required=False)
parser.add_argument('-mask', dest='mask', help='Netmask', required=False)
parser.add_argument('-gw', dest='gw', help='Gateway', required=False)

parser.set_defaults(dhcp=False)
args = parser.parse_args()

# configuration file
FILE="foo-" + args.iface
print "Configuring File: %s" % FILE

def get_file(name):
    foo=open(name, "r")
    lines = foo.read()
    foo.close()
    return lines

def set_file(name, lines):
    foo=open(name, "w")
    foo.write(lines)
    foo.close()

def validate_ip(ip):
    # Format
    try:
        socket.inet_aton(ip)
        # DAD
#       if os.system('ping -c 1 ' + ip) == 0:
#           print "do not use it"
#       else:
#           print "use it"
    except socket.error:
        sys.exit(1)

def entry_update(where, pattern, value):
    content = get_file(where)
    found = re.search(pattern + "=.*", content)
    if not found:
        set_file(where, content + pattern + "=%s\n" % value)
    else:
        new = re.sub(pattern + "=.*", pattern + "=%s" % value, content)
        set_file(where, new)

def entry_erase(where, pattern):
    # read file
    foo=open(where, "r")
    lines = foo.readlines()
    foo.close()
    # write file
    foo=open(where, "w")
    for line in lines:
        found = re.search(pattern + "=.*", line)
        if found:
            found = False
        else:
            foo.write(line)
    foo.close()

if args.dhcp: 
    # DHCP
    print "DHCP: True"
    entry_update(FILE, "BOOTPROTO", "dhcp")
    entry_erase(FILE, "IPADDR")
    entry_erase(FILE, "NETMASK")
    entry_erase(FILE, "GATEWAY")
else:
    # Static
    if not args.ip or \
       not args.mask or \
       not args.gw:
        print "Please provide IP Address, Mask & Gateway"
        parser.print_usage()
        sys.exit(1)

    # Static/DHCP
    print "DHCP: False"
    entry_update(FILE, "BOOTPROTO", "none")

    # IP Address
    print "IP Address: " + args.ip
    validate_ip(args.ip)
    entry_update(FILE, "IPADDR", args.ip)

    # Mask
    print "Netmask: " + args.mask
    entry_update(FILE, "NETMASK", args.mask)

    # Gateway
    print "Gateway: " + args.gw
    entry_update(FILE, "GATEWAY", args.gw)

# os.system("echo Restarting Network ...")
# os.system("service network restart")


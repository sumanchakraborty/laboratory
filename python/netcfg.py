#!/usr/bin/python

import re
import os
import string
import argparse

FILE="foo"

# configuration files
# -------------------
# iface - dhcp, ip, mask, network
# network - hostname, gateway
# dns - dns
file_iface="/etc/sysconfig/network-scripts/ifcfg-eth0"
file_network="/etc/sysconfig/network"
file_dns="/etc/resolv.conf"

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
parser.add_argument('-net', dest='net', help='Network', required=False)
parser.add_argument('-gw', dest='gw', help='Gateway', required=False)
parser.add_argument('-static', dest='static', help='Static/DHCP', required=False)
parser.add_argument('-host', dest='host', help='HostName', required=False)
parser.add_argument('-dns', dest='dns', help='DNS', required=False)
# parser.add_argument('-dns', dest='dns', help='DNS', required=False, action='append')

args = parser.parse_args()

# IP Address
if args.ip: 
    content = get_file(FILE)
    found = re.search("IPADDR=.*", content)
    if not found:
        set_file(FILE, content + "IPADDR=%s\n" % args.ip)
    else:
        found = False
        new = re.sub("IPADDR=.*", "IPADDR=%s" % args.ip, content)
        set_file(FILE, new)

# Mask
if args.mask: 
    print args.mask
    content = get_file(FILE)
    found = re.search("NETMASK=.*", content)
    if not found:
        set_file(FILE, content + "NETMASK=%s\n" % args.mask)
    else:
        found = False
        new = re.sub("NETMASK=.*", "NETMASK=%s" % args.mask, content)
        set_file(FILE, new)

# Network
if args.net: 
    print args.net
    content = get_file(FILE)
    found = re.search("NETWORK=.*", content)
    if not found:
        set_file(FILE, content + "NETWORK=%s\n" % args.net)
    else:
        found = False
        new = re.sub("NETWORK=.*", "NETWORK=%s" % args.net, content)
        set_file(FILE, new)

# Gateway
if args.gw: 
    print args.gw
    content = get_file(FILE)
    found = re.search("GATEWAY=.*", content)
    if not found:
        set_file(FILE, content + "GATEWAY=%s\n" % args.gw)
    else:
        found = False
        new = re.sub("GATEWAY=.*", "GATEWAY=%s" % args.gw, content)
        set_file(FILE, new)

# Static/DHCP
if args.static: 
    print args.static
    content = get_file(FILE)
    found = re.search("BOOTPROTO=.*", content)
    if not found:
        set_file(FILE, content + "BOOTPROTO=%s\n" % args.static)
    else:
        found = False
        new = re.sub("BOOTPROTO=.*", "BOOTPROTO=%s" % args.static, content)
        set_file(FILE, new)

# Hostname
if args.host: 
    print args.host
    content = get_file(FILE)
    found = re.search("HOSTNAME=.*", content)
    if not found:
        set_file(FILE, content + "HOSTNAME=%s\n" % args.host)
    else:
        found = False
        new = re.sub("HOSTNAME=.*", "HOSTNAME=%s" % args.host, content)
        set_file(FILE, new)

# DNS
if args.dns: 
    print args.dns
    content = get_file(FILE)
    set_file(FILE, content + "nameserver %s\n" % args.dns)


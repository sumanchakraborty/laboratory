#!/usr/bin/python

# Set log level to benefit from Scapy warnings
import logging
logging.getLogger("scapy").setLevel(1)

from scapy.all import *
# from scapy.all import send, IP, ICMP

class Test(Packet):
    name = "Test packet"
    fields_desc = [ ShortField("test1", 1),
                    ShortField("test2", 2) ]

def make_test(x,y):
    return Ether()/IP()/Test(test1=x,test2=y)

# make_test(42,666)
# packet = IP(src="10.0.99.100",dst="10.1.99.100")/ICMP()/"Hello World"
# packet.ttl=22

# send(packet)
sniff(iface="eth0", prn=lambda x: x.show())


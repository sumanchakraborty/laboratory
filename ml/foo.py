#!/usr/bin/python

import threading
import time
from scapy.all import *

class myThread (threading.Thread):
    def __init__(self, threadID, name):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name

    def run(self):
        print "Starting " + self.name
        # Get lock to synchronize threads
        threadLock.acquire()
        if self.threadID == 1:
            capture(self.name)
        if self.threadID == 2:
            transact(self.name)
        # Free lock to release next thread
        threadLock.release()

def packet_callback(pkt):
    print pkt.show()

def capture(threadName):
    print "capture ..."
#   sniff(iface="eth0", prn=lambda x: x.show())
    p = sniff(iface='eth0', filter="icmp", count=1, prn=packet_callback)
#   p.summary()

def transact(threadName):
    print "transact ..."
    packet = IP(src="10.0.99.100",dst="10.1.99.100")/ICMP()/"Hello World"
    #   packet.ttl=22
    send(packet)

threadLock = threading.Lock()
threads = []

# Thread-1 = capture
# Thread-2 = transact

# Create new threads
thread1 = myThread(1, "capture")
thread2 = myThread(2, "transact")

# Start new Threads
thread1.start()
time.sleep(2)
thread2.start()

# Add threads to thread list
threads.append(thread1)
threads.append(thread2)

# Wait for all threads to complete
for t in threads:
    t.join()

print "Exiting Main Thread"


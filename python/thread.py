#!/usr/bin/python

import threading
import time

class myThread (threading.Thread):
    def __init__(self, threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter
    def run(self):
        # Get lock to synchronize threads
        threadLock.acquire()
        print "Starting " + self.name
        print_time(self.name, self.counter, 3)
        # Free lock to release next thread
        threadLock.release()

def print_time(threadName, delay, counter):
    while counter:
        time.sleep(delay)
        print "%s: %s" % (threadName, time.ctime(time.time()))
        counter -= 1

threadLock = threading.Lock()
threads = []

# Create new threads
thread1 = myThread(1, "Thread-1", 1)
thread2 = myThread(2, "Thread-2", 2)

# Add threads to thread list
threads.append(thread1)
threads.append(thread2)

# Start new Threads
for t in threads:
    t.start()

# Wait for all threads to complete
for t in threads:
    t.join()

print "Exiting Main Thread"

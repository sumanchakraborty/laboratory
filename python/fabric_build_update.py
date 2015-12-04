
'''
Lab - Average Uptime

Write a script that uses the Fabric library to poll a group of hosts for their
uptimes, and displays their average uptime for the user.

cd /var/tmp/
/usr/bin/strikepack.rb D update_vm-183596-234843.bps update.tar.bz2
tar -xjf update.tar.bz2
cd /var/tmp/update

--- setup.sh ---
for SCRIPT in updatesteps/*
do
    if [ -f $SCRIPT -a -x $SCRIPT ]
    then
    $SCRIPT
    fi
done

chmod +x setup.sh
./setup.sh

'''

#!/usr/bin/python

from fabric import tasks
from fabric.api import run
from fabric.api import env
from fabric.network import disconnect_all

env.password = 'reDref3u'
env.hosts = ['root@10.216.110.201']

def uptime():
    res = run('ls -la')
    res = run('cat /proc/uptime')
    #
    # Now, examine the result and extract the average uptime
    #

def install():
    res = run('ls -la')

def main():
    uts_dict = tasks.execute(uptime)
    # 
    # Now, calculate average uptime...
    #
    disconnect_all() # Call this when you are done, or get an ugly exception!

if __name__ == '__main__':
    main()


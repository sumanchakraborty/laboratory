
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

import os, sys, json
from fabric import tasks
from fabric.api import run, env
from fabric.context_managers import cd
from fabric.network import disconnect_all

CONFIG = 'script.json'
URL = "http://10.218.2.22/builds/main/254651/updates/update_vm-183596-254651.bps"

def configure():
    with open(CONFIG) as data_file:    
        data = json.load(data_file)
        node_count = len(data["nodes"])
        print "URL: " + data["url"]
        print "Node Count: " + str(node_count)
        index = 0
        env.user = 'root'
        env.password = 'reDref3u'
        env.hosts = []
        while index < node_count:
            print "Node: " + data["nodes"][index]
            env.hosts.append(data["nodes"][index])
            index = index + 1

def test():
    res = run("date")
    res = run("uname -a")
    res = run("pwd")
    res = run("ls")

def reboot():
    res = run("reboot")

def download():
    with cd('/var/tmp'):
        res = run("rm -rf update*")
        res = run("wget -nv -O update.bps "+ URL)
        res = run("/usr/bin/strikepack.rb D update.bps update.tar.bz2")
        res = run("tar -xjf update.tar.bz2")

def install():
    with cd('/var/tmp/update'):
        res = run("touch setup.sh")
        res = run("echo '#!/bin/sh' >> setup.sh")
        res = run("echo 'for SCRIPT in updatesteps/*' >> setup.sh")
        res = run("echo 'do' >> setup.sh")
        res = run("echo 'if [ -f $SCRIPT -a -x $SCRIPT ]' >> setup.sh")
        res = run("echo 'then' >> setup.sh")
        res = run("echo '$SCRIPT' >> setup.sh")
        res = run("echo 'fi' >> setup.sh")
        res = run("echo 'done' >> setup.sh")
        res = run('chmod +x setup.sh')
        res = run('./setup.sh')

def main():
    configure()
    uts_dict = tasks.execute(test)
#   uts_dict = tasks.execute(download)
#   uts_dict = tasks.execute(install)
#   uts_dict = tasks.execute(reboot)
    disconnect_all() # Call this when you are done, or get an ugly exception!

if __name__ == '__main__':
    main()


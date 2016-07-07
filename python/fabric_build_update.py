
'''
suman.chakraborty@gmail.com

Script that uses the fabric library to install a build 
by reading json configuration file.

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

URL = "http://foo"
CONFIG = 'fabric_build_update.json'

def configure():
    global URL
    with open(CONFIG) as data_file:    
        data = json.load(data_file)
        node_count = len(data["nodes"])
        URL = data["url"]
        print "URL: " + URL
        print "Node Count: " + str(node_count)
        index = 0
        env.user = 'root'
        env.password = 'reDref3u'
        env.hosts = []
        while index < node_count:
            print "Node: " + data["nodes"][index]
            env.hosts.append(data["nodes"][index])
            index = index + 1

def reboot():
    res = run("reboot")

def download():
    global URL
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
    uts_dict = tasks.execute(download)
    uts_dict = tasks.execute(install)
    uts_dict = tasks.execute(reboot)
    disconnect_all() # Call this when you are done, or get an ugly exception!

if __name__ == '__main__':
    main()


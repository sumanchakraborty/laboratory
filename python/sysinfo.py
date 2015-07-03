#!/usr/bin/python

import os
import sys
import platform
# import tabulate

def sysinfo( ) :
    print "File: %s" % __file__
    os.system("date")
    print "%s" % "----------------------------"

    print "System: %s, " % platform.system(), \
          "Release: %s, " % platform.release(), \
          "Machine: %s" % platform.machine()

    print "Implementation: %s, " % platform.python_implementation(), \
          "Version: %s" % platform.python_version()


    return

def sysinfo_table( ) :
    print "File: %s" % __file__
    os.system("date")
    print "%s" % "----------------------------"

    table = [["System",platform.system()],\
             ["Release",platform.release()], \
             ["Machine",platform.machine()], \
             ["Implementation",platform.python_implementation()], \
             ["Version",platform.python_version()]]

    print tabulate(table)

    return

sysinfo()
# sysinfo_table()

#!/usr/bin/python

import telnetlib

HOST = "10.205.30.86"
USER = "suman"
PASS = "39039820"
SCRIPT = "tmp.py"

def connect( ):
    session = telnetlib.Telnet(HOST)

    print "login:" + USER
    session.read_until("login: ")
    session.write(USER + "\n")

    print "password:" + PASS
    session.read_until("Password: ")
    session.write(PASS + "\n")

#   session.write("date\n")
#   session.write("pwd\n")
    session.write("ls -la\n")

#   open python prompt
    session.write("python\n")

    return session

def close( session ):
#   close python & shell
    session.write("exit()\n")
    session.write("exit\n")

    print session.read_all()

#   close telnet
    session.close()

    return

if __name__ == '__main__':

#   open session
    session = connect()

#   open file, read each line & close
    file = open(SCRIPT, 'r')
    lines = file.readlines()
    file.close()

#   execute file
    for line in lines:
        session.write(line)

#   close session
    close(session)


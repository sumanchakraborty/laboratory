#!/usr/bin/python

import os
import sys
import ftplib
import telnetlib

# common
CRLF = "\r\n"
SCRIPT = sys.argv[1]
XML = sys.argv[2]
LOG_SETUP = "setup.log"
LOG_CONNECT = "error.log"
LOG_ERROR = "error.log"

# prompts
PROMPT1 = [': ']
PROMPT2 = ['>', '\$']

# linux
HOST = "10.10.7.1"
USER = "suman"
PASS = "ixia2005!"
PATH = "/home/suman/workload"

# windows
#   HOST = "10.205.30.112"
#   USER = "administrator"
#   PASS = "ixia2005!"
#   PATH = "D:\\shared\\tanuman"

class logger(object):
    def __init__(self):
        self.terminal = sys.stdout
        self.log = open(LOG_CONNECT, "a")

    def write(self, message):
        self.terminal.write(message)
        self.log.write(message)  

def move( session ):
    print "moving to ... %s" % PATH
    tokens = PATH.split(":")
    if len(tokens) == 1:
        session.write("cd %s" % tokens[0] + CRLF)
        session.expect(PROMPT2)
    else:
        session.write(tokens[0] + ":" + CRLF)
        session.expect(PROMPT2)
        session.write("cd %s" % tokens[1] + CRLF)
        session.expect(PROMPT2)
    return 0

def upload( ):
    print "uploading files ..."
    session = ftplib.FTP(HOST,USER,PASS)
    session.set_debuglevel(2)
    session.cwd(PATH)
    script = open(SCRIPT, "rb")
    command = "STOR " + SCRIPT
    session.storbinary(command, script)
    script.close()
    xml = open(XML, "rb")
    command = "STOR " + XML
    session.storbinary(command, xml)
    xml.close()
    session.quit()
    return 0

def download( ):
    print "downloading files ..."
    session = ftplib.FTP(HOST,USER,PASS)
    session.set_debuglevel(2)
    session.cwd(PATH)
    log = open(LOG_SETUP, "wb")
    command = "RETR " + LOG_SETUP
    session.retrbinary(command, log.write)
    log.close()
    session.quit()
    return 0

def delete( session ):
    print "removing files ..."
    command = "rm -rf " + SCRIPT + " " + XML + " " + LOG_SETUP
    session.write(command + CRLF)
    session.expect(PROMPT2)
    return 0

def merge( ):
    print "merging log files ..."
    os.system("rm -rf " + LOG_ERROR)
    os.system("cat " + LOG_CONNECT + " >> " + LOG_ERROR)
    os.system("cat " + LOG_SETUP + " >> " + LOG_ERROR)
    os.system("rm -rf " + LOG_CONNECT)
    os.system("rm -rf " + LOG_SETUP)
    return 0

def connect( ):
    print "connecting ..."
    session = telnetlib.Telnet(HOST)
    session.expect(PROMPT1)
    session.set_debuglevel(2)
    session.write(USER + CRLF)
    session.expect(PROMPT1)
    session.write(PASS + CRLF)
    session.expect(PROMPT2)
    return session

def close( session ):
    print "exiting ..."
    session.write("exit()" + CRLF)
    session.expect(PROMPT2)
    session.write("exit" + CRLF)
    session.close()
    return

if __name__ == '__main__':
    sys.stderr = logger()
    upload()
    session = connect()
    move(session)
    command = "python" + " " + SCRIPT + " " + XML
    session.write(command + CRLF)
    session.expect(PROMPT2)
    download()
    delete(session)
    close(session)
    merge()


#!/usr/bin/python

import os
import sys
import telnetlib

# common
SCRIPT = sys.argv[1]
CRLF = "\r\n"

# prompts
PROMPT1 = [': ']
PROMPT2 = ['>', '\$']
PROMPT3 = ['>>> ']
PROMPT4 = ['... ']

# linux
HOST = "10.205.30.86"
USER = "suman"
PASS = "39039820"
PATH = "/home/suman/workload"

# windows
#   HOST = "10.205.30.112"
#   USER = "administrator"
#   PASS = "ixia2005!"
#   PATH = "D:\\shared\\tanuman"

def move( session ):
    print "moving to %s" % PATH
    tokens = PATH.split(":")
    if len(tokens) == 1:
        session.write("cd %s" % tokens[0] + CRLF)
        session.expect(PROMPT2)
    else:
        session.write(tokens[0] + ":" + CRLF)
        session.expect(PROMPT2)
        session.write("cd %s" % tokens[1] + CRLF)
        session.expect(PROMPT2)

def connect( ):
    session = telnetlib.Telnet(HOST)
    session.expect(PROMPT1)

    session.set_debuglevel(2)

    session.write(USER + CRLF)
    session.expect(PROMPT1)

    session.write(PASS + CRLF)
    session.expect(PROMPT2)

    move(session)
    session.write("python" + CRLF)
    session.expect(PROMPT3)

    return session

def close( session ):
    session.write("exit()" + CRLF)
    session.expect(PROMPT2)

    session.write("exit" + CRLF)

    session.close()

    return

if __name__ == '__main__':

    modulePrompt = False
    session = connect()

    file = open(SCRIPT)
    for line in file:
        nline = line.rstrip()
        if nline:
            if "#" in nline:
                continue
            elif "return 0" in nline:
                modulePrompt = False
                session.write(nline + CRLF + CRLF)
                session.expect(PROMPT3)
            elif "def " in nline:
                modulePrompt = True
                session.write(nline + CRLF)
                session.expect(PROMPT4)
            else:
                session.write(nline + CRLF)
                if modulePrompt:
                    session.expect(PROMPT4)
                else:
                    session.expect(PROMPT3)
    file.close()

    close(session)


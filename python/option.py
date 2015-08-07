 import optparse
   2 
   3 if __name__=="__main__":
   4     parser = optparse.OptionParser("usage: %prog [options] arg1 arg2")
   5     parser.add_option("-H", "--host", dest="hostname",
   6                       default="127.0.0.1", type="string",
   7                       help="specify hostname to run on")
   8     parser.add_option("-p", "--port", dest="portnum", default=80,
   9                       type="int", help="port number to run on")
  10 
  11     (options, args) = parser.parse_args()
  12     if len(args) != 2:
  13         parser.error("incorrect number of arguments")
  14     hostname = options.hostname
  15     portnum = options.portnum

import argparse

parser = argparse.ArgumentParser(description='Description of your program')
parser.add_argument('-f','--foo', help='Description for foo argument', required=True)
parser.add_argument('-b','--bar', help='Description for bar argument', required=True)
args = vars(parser.parse_args())

if args['foo'] == 'Hello':
    # code here

if args['bar'] == 'World':
    # code here
    

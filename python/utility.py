
import re
import os
import sys
import string
import socket
import platform
import fcntl
import struct
import array
import ipaddress
import subprocess

SIOCGIFCONF = 0x8912
MAXBYTES = 8096

FILE_LOG = "/var/log/netadmin.log"

class logger(object):
    def __init__(self, filename=FILE_LOG):
        self.terminal = sys.stdout
        self.log = open(filename, "a")

    def write(self, message):
        self.log.write(message)
        self.terminal.write(message)

    def debug(self, message):
        message += "\n"
        self.log.write("Debug: " + message)

def execute(command):
    sys.stdout.log.write('Command: ' + command + '\n')
    os.system(command + ' &> /dev/null')
#   try:
#       proc = subprocess.Popen(command, 
#                               shell = True,
#                               stdout = subprocess.PIPE)
#                             # stderr = subprocess.PIPE)
#       out, _ = proc.communicate()
#       sys.stdout.log.write(out + '\n')
#   except:
#       sys.stdout.log.write('Exception !!' + '\n')
#       sys.exit(1)

def is_controller():
    if os.path.exists('/etc/vmenv'):
        return True
    else:
        return False

def is_single_interface():
    if os.path.exists('/etc/single_interface'):
        return True
    else:
        return False

def register_host(ifname):
    if not is_controller():
        return True
    elif is_single_interface():
        return True
    elif ifname == "eth0":
        return True

def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        return socket.inet_ntoa(fcntl.ioctl(
            s.fileno(),
            0x8915,  # SIOCGIFADDR
            struct.pack('256s', ifname[:15])
        )[20:24])
    except:
        # print "Warning: %s has no IP address!" % ifname
        return "0.0.0.0"
        # sys.exit(1)

def get_file(name):
    foo=open(name, "r")
    lines = foo.read()
    foo.close()
    return lines

def set_file(name, lines):
    foo=open(name, "w")
    foo.write(lines)
    foo.close()

def search_replace(where, pattern, value):
    content = get_file(where)
    found = re.search(pattern, content)
    if found:
        new = re.sub(pattern, value, content)
        set_file(where, new)

def iface_up(ifname):
    # set some symbolic constants
    SIOCGIFFLAGS = 0x8913
    null256 = '\0'*256

    # create a socket so we have a handle to query
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # call ioctl() to get the flags for the given interface
    result = fcntl.ioctl(s.fileno(), SIOCGIFFLAGS, ifname + null256)

    # extract the interface's flags from the return value
    flags, = struct.unpack('H', result[16:18])

    return flags & 1

def validate_iface(iface):
    if iface != "eth0" and \
       iface != "ctrl0":
        print "ERROR: %s is not valid interface!" % iface
        sys.exit(1)
    if is_controller() and \
       is_single_interface() and \
       iface == "eth0":
        print "ERROR: %s is not valid interface!" % iface
        sys.exit(1)
    if iface == "ctrl0" and \
       not is_controller():
        print "ERROR: %s is not valid interface!" % iface
        sys.exit(1)
    if not iface_up(iface):
        # print "Warning: Interface is down, bringing up ..."
        os.system('ifup ' + iface)

def get_netmask_string(IP, MASK):
    try:
        IPMASK = IP + '/' + MASK
        interface = ipaddress.IPv4Interface(IPMASK)
        net = interface.network.network_address
        NETMASK = str(net) + '/' + MASK
        netmask = ipaddress.IPv4Network(NETMASK)
        return str(netmask.netmask)
    except Exception, e:
        print "Error: " + str(e)
        sys.exit(1)

def validate_ip(IP, MASK):
    try:
        IPMASK = IP + '/' + MASK
        interface = ipaddress.IPv4Interface(IPMASK)
        net = interface.network.network_address
        ip = ipaddress.IPv4Address(IP)
        if ip == net:
            print "Error: %s is Network Address" % IP
            sys.exit(1)
        if ip.is_loopback:
            print "Error: %s is Loopback Address" % IP
            sys.exit(1)
        if ip.is_multicast:
            print "Error: %s is Multicast Address" % IP
            sys.exit(1)
        NETMASK = str(net) + '/' + MASK
        netmask = ipaddress.IPv4Network(NETMASK)
        if netmask.broadcast_address == ip:
            print "Error: %s is Broadcast Address" % IP
            sys.exit(1)
    except Exception, e:
        print "Error: " + str(e)
        sys.exit(1)

def validate_ip_format(ip):
    try:
        socket.inet_aton(ip)
        if ip.count('.') != 3:
            print "ERROR: %s is in bad format!" % ip
            sys.exit(1)
    except socket.error:
        print "ERROR: %s is in bad format!" % ip
        sys.exit(1)

def validate_ip_dad(ip):
    # print "Checking address reachability ..."
    if not os.system('ping -c1 ' + ip + ' > /dev/null'):
        print "ERROR: %s used by another system!" % ip
        sys.exit(1)

def validate_ip_mask(mask):
    try:
        if int(mask) not in range(1, 31):
            print "Error: %s is a bad value! " \
                  "Valid range is [1-31]." % mask
            sys.exit(1)
    except ValueError:
        print "Error: %s is in bad format!" % mask
        sys.exit(1)

def localifs():
    """
    Used to get a list of the up interfaces and associated IP addresses
    on this machine (linux only).

    Returns:
    List of interface tuples.  Each tuple consists of
    (interface name, interface IP)
    """
    global SIOCGIFCONF
    global MAXBYTES

    arch = platform.architecture()[0]

    # I really don't know what to call these right now
    var1 = -1
    var2 = -1
    if arch == '32bit':
        var1 = 32
        var2 = 32
    elif arch == '64bit':
        var1 = 16
        var2 = 40
    else:
        raise OSError("Unknown architecture: %s" % arch)

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    names = array.array('B', '\0' * MAXBYTES)
    outbytes = struct.unpack('iL', fcntl.ioctl(
        sock.fileno(),
        SIOCGIFCONF,
        struct.pack('iL', MAXBYTES, names.buffer_info()[0])
        ))[0]

    namestr = names.tostring()
    return [(namestr[i:i+var1].split('\0', 1)[0], socket.inet_ntoa(namestr[i+20:i+24])) \
            for i in xrange(0, outbytes, var2)]

def param_update(where, key, separator, value):
    content = get_file(where)
    found = re.search(key + separator + ".*", content)
    if not found:
        set_file(where, content + key + separator + "%s\n" % value)
    else:
        new = re.sub(key + separator + ".*", key + separator + "%s" % value, content)
        set_file(where, new)

def param_erase(where, key, separator):
    # read file
    foo = open(where, "r")
    lines = foo.readlines()
    foo.close()
    # write file
    foo = open(where, "w")
    for line in lines:
        found = re.search(key + separator + ".*", line)
        if found:
            found = False
        else:
            foo.write(line)
    foo.close()


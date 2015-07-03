import ConfigParser as ConfigParser
from subprocess import Popen
import sys, os

if __name__ == "__main__":

argList = sys.argv[1:]
print "arguments are = %s" %argList

iniToRead = argList[0]

if os.path.exists(iniToRead):
    fid = file(iniToRead, "r")
    cp = ConfigParser.ConfigParser()
    cp.readfp(fid)

    configDict = {}
    for sects in cp.sections():
        options = cp.options(sects)
        for option in options:
            configDict[option] = cp.get(sects, option)

#print configDict

#print "Getting the list of existing VMs from %s..." % configDict['host']

#fp = open('tmp.txt','w')   
#strToExec = 'C:\Program Files\VMware\VMware OVF Tool\ovftool.exe vi://' + configDict['username'] + ':' + configDict['password'] + '@' + configDict['host'] 
#proc = Popen(strToExec, stdout = fp)
#fp.close()

            vmList = []
            fp = open('tmp.txt','r')
            for lns in fp.readlines():
    vmList.append(lns.strip())   
    fp.close()
    print vmList

    fp = open('Execution_log.txt','w') 
    for port in range(0, int(configDict['number'])):
        try:
        strToExec = 'C:\Program Files\VMware\VMware OVF Tool\ovftool.exe --acceptAllEulas --powerOn -ds=datastore1 -n=Port-' + str(port) + ' --net:"IxVM Management Network=' + configDict['ixvm management network'] + '\"' + ' --net:\"IxVM Test Network 1=' + configDict['ixvm test network 1'] + '\" ' + configDict['ovalocation'] + ' vi://' + configDict['username'] + ':' + configDict['password'] + '@' + configDict['host']
        proc = Popen(strToExec, stdout = fp)
        except:
    print "!ERROR - Failed to deploy."
    fp.close()


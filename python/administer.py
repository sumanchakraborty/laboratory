
# SC  root/reDref3u
# NP  root/6eheyaDe
# HV  ixl-vm-dev-esx-2 (10.216.110.205)
#     root/1x1ac0m.c0m

# from fabric.api import *
from fabric.api import *

env.host_string='10.216.110.200'
env.user='root'
env.password='reDref3u'

def command(command):
    try:
        with hide('running', 'stdout', 'stderr'):
            results = run(command)
    except:
        results = 'Error'
    return results

print command('date')
print command('uname -s')
print command('df')


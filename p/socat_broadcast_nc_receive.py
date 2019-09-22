#!/usr/bin/env python3

import subprocess
import re
import sys

ipresult = subprocess.run(['ip', 'addr'], stdout=subprocess.PIPE)
#print(ipresult.stdout)
#print(type(ipresult.stdout))
brd_matchobj = re.search(' brd (1[.0-9]*)', ipresult.stdout.decode())
brd = brd_matchobj.group(1)
subprocess.run(['nc', '-u', '-l', brd, '18763'])

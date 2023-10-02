#!/usr/bin/env python3

import sys
import subprocess
import re
import shutil
from os import listdir
from os.path import isfile

folderpath = '.'

all_interest = []
advices = [f for f in listdir(folderpath) if f.endswith('.pdf') and f != 'in.pdf' and f != 'out.pdf']

for doc in advices:
 if doc.startswith('Statement_'):
  continue
 shutil.copyfile(doc, 'in.pdf')
 com_proc = subprocess.run('sudo docker run --rm -i --user "$(id -u):$(id -g)" --workdir /data -v "$PWD:/data" jbarlow83/ocrmypdf in.pdf out.pdf', shell=True, check=True, capture_output=True)
 print(com_proc.stderr, file=sys.stderr)
 print(com_proc.stdout, file=sys.stderr)
 com_proc = subprocess.run('pdftotext -layout out.pdf out.txt', shell=True, check=True, capture_output=True)
 print(com_proc.stderr, file=sys.stderr)
 print(com_proc.stdout, file=sys.stderr)
 com_proc = subprocess.run(['perl', '-wln', '-e', r'print if /\bInterest\b.+\+\s*HKD/', 'out.txt'], check=True, capture_output=True)
 print(com_proc.stderr, file=sys.stderr)
 print(com_proc.stdout, file=sys.stderr)
 outln = com_proc.stdout.splitlines()
 assert 1 == len(outln)
 numgrp = re.findall(r'\bInterest\b.+\+\s*HKD\s*([0-9]+\.?[0-9]*)', outln[0].decode())
 assert 1 == len(numgrp)
 #print(numgrp[0])
 all_interest.append(numgrp[0])

finalstr = '+'.join(all_interest)+'\n'
print(finalstr)
#Path('final.txt').write_text('+'.join(all_num))
com_proc = subprocess.run(['bc'], input=finalstr.encode(), check=True, capture_output=True)
print(com_proc.stderr, file=sys.stderr)
print(com_proc.stdout, file=sys.stderr)

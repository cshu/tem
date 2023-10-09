#!/usr/bin/env python3

import sys
import subprocess
import re
import shutil
from pathlib import Path
from os import listdir
from os.path import isfile
from datetime import datetime

p_date = r'(\b[0-3][0-9]\-[A-Z]{3}\-[0-9]{4}\b)'
p_amount = r'(([0-9]+,)*[0-9]+\.?[0-9]*\b)'
scr_filename = sys.argv[0]
if 3!=len(sys.argv):
 raise Exception('Must provide exactly 2 args as range like %Y%m %Y%m (first one inclusive, second one exclusive)')
begin_month = sys.argv[1]
end_month = sys.argv[2]
if len(begin_month)!=6 or len(end_month)!=6:
 raise Exception('Must provide exactly 2 args as range like %Y%m %Y%m (first one inclusive, second one exclusive)')
begin_month=datetime.strptime(begin_month, '%Y%m')
end_month=datetime.strptime(end_month, '%Y%m')
print('Range to search: ', begin_month, end_month)
min_dt=datetime.max
max_dt=datetime.min
finallst = []

def refr_max_min_dt(txndt):
 global min_dt
 global max_dt
 if txndt < min_dt:
  min_dt = txndt
 elif txndt > max_dt:
  max_dt = txndt

def chk_hist(hist):
 #retval = []
 for ln in hist:
  numgrp = re.findall(r'^\s*'+p_date+r'\s+(.*息.*)\s+\+'+p_amount+r'\s+'+p_amount+r'\s*$', ln)
  if len(numgrp) > 1:
   raise Exception('Unknown pattern')
  elif not numgrp:
   continue
  txndt = re.sub(r'\s','',numgrp[0][0]).replace('-','')
  txndt = datetime.strptime(txndt, '%d%b%Y')
  if begin_month <= txndt < end_month:
   refr_max_min_dt(txndt)
   amount = numgrp[0][2].replace(',','')
   finallst.append((txndt,re.sub(r'\s{3,}','   ',numgrp[0][1].strip()),amount,))
   print(ln)
   #retval.append(numgrp[0][2])
 #return retval

folderpath = '.'

stmtfnmp = re.compile(r'^20[0-9]{2}\-[0-1][0-9]( Monthly Statement|月結單)\.pdf$')
stmts = [f for f in listdir(folderpath) if stmtfnmp.match(f)]
print(stmts)
#all_num = []

for doc in stmts:
 print(doc)
 shutil.copyfile(doc, 'out.pdf')
 com_proc = subprocess.run('pdftotext -layout out.pdf out.txt', shell=True, check=True, capture_output=True)
 print(com_proc.stderr, file=sys.stderr)
 print(com_proc.stdout, file=sys.stderr)
 hist = Path('out.txt').read_text().splitlines()
 chk_hist(hist)

finallst.sort()
print('LIST OF ALL:')
print(*finallst, sep='\n')
print('min datetime: ', min_dt)
print('max datetime: ', max_dt)
#//? now you have a big question: should you use exchange rate of each day (different exchange rate for every single day) or should you use average exchange rate of the year?

#finalstr = '+'.join(all_num)+'\n'
#print(finalstr)
##Path('final.txt').write_text('+'.join(all_num))
#com_proc = subprocess.run(['bc'], input=finalstr.encode(), check=True, capture_output=True)
#print(com_proc.stderr, file=sys.stderr)
#print(com_proc.stdout, file=sys.stderr)

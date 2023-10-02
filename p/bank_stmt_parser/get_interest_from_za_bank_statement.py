#!/usr/bin/env python3

import sys
import subprocess
import re
import shutil
from pathlib import Path
from os import listdir
from os.path import isfile
from datetime import datetime

p_date = r'(\b[0-3][0-9]\s*[A-Z][a-z]{2}\s*[0-9]{4}\b)'
p_amount = r'(\b([0-9]+,)*[0-9]+\.?[0-9]*\b)'
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
otherlst = []
tdlst = []
#finallst = []

def refr_max_min_dt(txndt):
 global min_dt
 global max_dt
 if txndt < min_dt:
  min_dt = txndt
 elif txndt > max_dt:
  max_dt = txndt

def find_sep_for_txn_and_td(txt):
 for idx, ln in enumerate(txt):
  if -1 != ln.find('Foreign-Currency Savings'):
   retval = idx
   break
 else:
  raise Exception('Cannot find separator')
 return retval

def chk_td(td):
 #retval = []
 for ln in td:
  numgrp = re.findall(p_date+r'\s+'+p_amount+r'\s+HKD\s+[0-9]+\.?[0-9]*.\s+'+p_date+r'\s+'+p_amount, ln, re.IGNORECASE)
  if len(numgrp) > 1:
   raise Exception('Unknown pattern')
  elif not numgrp and re.findall(r'\bImportant\s+Notice', ln):
   break
  elif not numgrp:
   continue
  deposit_d = re.sub(r'\s','',numgrp[0][0])
  principal = numgrp[0][1].replace(',','')
  maturity_d = re.sub(r'\s','',numgrp[0][3])
  maturity_amt = numgrp[0][4].replace(',','')
  deposit_d = datetime.strptime(deposit_d, '%d%b%Y')
  maturity_d = datetime.strptime(maturity_d, '%d%b%Y')
  if begin_month <= maturity_d < end_month:
   refr_max_min_dt(maturity_d)
   amount = '('+maturity_amt+'-'+principal+')'
   tdlst.append((maturity_d, 'td', amount, deposit_d,))
   print(ln)
  #retval.append('('+mature+'-'+principal+')')
 else:
  raise Exception('Cannot find td end')
 #return retval

def chk_hist(hist):
 #retval = []
 for ln in hist:
  numgrp = re.findall(p_date+r'\s.*(\binterest\b|\bcoin\s+cash\s+rebate\b).*\s'+p_amount+r'\s+'+p_amount, ln, re.IGNORECASE)
  if len(numgrp) > 1:
   raise Exception('Unknown pattern')
  elif not numgrp:
   continue
  txndt = re.sub(r'\s','',numgrp[0][0])
  txndt = datetime.strptime(txndt, '%d%b%Y')
  if begin_month <= txndt < end_month:
   refr_max_min_dt(txndt)
   amount = numgrp[0][2].replace(',','')
   otherlst.append((txndt,numgrp[0][1],amount,'',))
   print(ln)
   #retval.append(numgrp[0][2])
 #return retval

folderpath = '.'

stmts = [f for f in listdir(folderpath) if f.endswith('.pdf') and f.startswith('Statement_')]
#all_num = []

for doc in stmts:
 print(doc)
 shutil.copyfile(doc, 'out.pdf')
 com_proc = subprocess.run('pdftotext -layout out.pdf out.txt', shell=True, check=True, capture_output=True)
 print(com_proc.stderr, file=sys.stderr)
 print(com_proc.stdout, file=sys.stderr)
 txt = Path('out.txt').read_text().splitlines()
 sidx = find_sep_for_txn_and_td(txt)
 hist = txt[:sidx]
 td = txt[sidx+1:]
 chk_hist(hist)
 chk_td(td)
 #print(hist_num)
 #print(td_num)
 #all_num += hist_num
 #all_num += td_num

tdlst = list(set(tdlst))
finallst = tdlst + otherlst
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

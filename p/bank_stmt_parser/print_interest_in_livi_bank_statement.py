#!/usr/bin/env python3

import sys
import subprocess
import re
import shutil
from pathlib import Path
from os import listdir
from os.path import isfile
from datetime import datetime

scr_filename = sys.argv[0]
if 3!=len(sys.argv):
 raise Exception('Must provide exactly 2 args as range like %Y%m %Y%m (first one inclusive, second one exclusive)')
begin_month = sys.argv[1]
end_month = sys.argv[2]
if len(begin_month)!=6 or len(end_month)!=6:
 raise Exception('Must provide exactly 2 args as range like %Y%m %Y%m (first one inclusive, second one exclusive)')


folderpath = '.'

stmts = [f for f in listdir(folderpath) if f.endswith('.pdf') and ('livi_ConsoStmt_'+begin_month < f < 'livi_ConsoStmt_'+end_month)]
stmts.sort()
print(stmts)

for doc in stmts:
 print(doc)
 shutil.copyfile(doc, 'out.pdf')
 com_proc = subprocess.run('pdftotext -layout out.pdf out.txt', shell=True, check=True, capture_output=True)
 print(com_proc.stderr, file=sys.stderr)
 print(com_proc.stdout, file=sys.stderr)
 txt = Path('out.txt').read_text().splitlines()
 print_active=False
 for ln in txt:
  if '利息' in ln or 'Interest' in ln:
   print(ln)
   print_active=True
  elif print_active:
   print(ln)
   print_active=False


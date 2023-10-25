#!/usr/bin/env python3

import re
import sys
import os
import json
import argparse
import subprocess
import shutil
from datetime import datetime
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument('template')
parser.add_argument('-s', '--skip-parsing', help='Skip html posting details parsing, this is usually used when website is not common job board', action='store_true')
nmsce: argparse.Namespace = parser.parse_args()
tfile: str = nmsce.template
skip_parsing: bool = nmsce.skip_parsing
tobj: dict = json.loads(Path(tfile).read_text())


repjson: str = tobj['repjson']
rep: str = tobj['rep']
pdfrename: str = tobj['pdfrename']
outpdf: str = tobj['pdf']
outdocx: str = tobj['docx']
chatcl: str = tobj['chatcl']
chatsummary: str = tobj['chatsummary']
tdir: str = tobj['tdir']
ghdir: str = tobj['ghdir']
cthdir: str = os.path.join(ghdir, 'chat-ai-template-helper')
jppdir: str = os.path.join(ghdir, 'job-postings-parser')
repdir: str = os.path.join(ghdir, 'replace-docx-text')

text_html_from_xclip_file = os.path.join(tdir, 'text_html_from_xclip.html')
fields = text_html_from_xclip_file+'.fields.json'
kwlst = text_html_from_xclip_file+'.keywords.txt'

htmlstr: str = subprocess.check_output(['xclip', '-t', 'text/html', '-o', '-selection', 'clipboard']).decode()
Path(text_html_from_xclip_file).write_text(htmlstr)

cl: str = ''
company: str
title: str
recruiter: str
postingsrc: str

date_paragraph: str = '{dt:%B} {dt.day}, {dt.year}'.format(dt=datetime.now())
cl+=date_paragraph+'\n\n'

fullkws='Rust,Go,Golang,Java,J2EE,Jave EE,C,C#,.NET,VB.NET,Visual Basic,Visual Basic .NET,C++,C++11,C++14,C++17,C++20,JavaScript,JS,Flutter,Cordova,SQL,MySQL,SQLite,T-SQL,MS SQL,MSSQL,MS SQL Server,MSSQL Server,SQL Server,Oracle,PL/SQL,PostgreSQL,Postgres,Shell,AWK,Linux,Unix,AIX,Windows,Windows Server,Azure,Azure Functions,Azure App Service,APIM,Azure DevOps,Python,Python3,Python 3,Dart,PHP,React,ReactJS,React.js,Vue,VueJS,Vue.js,Angular,AngularJS,Angular.js,HTML5,HTML,XHTML,CSS,Node.js,NodeJS,Node,Nodejs,Selenium,Bash,iOS,Android,LDAP,Active Directory,GCP,Google Cloud Platform,AWS,IIS,ITIL,Information Technology Infrastructure Library,PRINCE2,Azure Pipelines,GitLab Pipelines,Git,GitHub,GitLab,GitHub Actions,Ansible,DevOps,DevSecOps,GAE,Google App Engine,TypeScript,Perl,ASP.NET,ASP.NET Core,.NET Core,PowerShell,ProjectWise,JavaFX,Swing,Crystal Reports,Crystal Report,WinForms,WinForm,VB,VBA,Bootstrap,jQuery,Vanilla JS,VanillaJS,RPC,RESTful,REST,REST API,RESTful API,REST APIs,RESTful APIs,Entity Framework,Maven,ASP.NET MVC,Visual C++,MFC,Hibernate,Spring,Spring Boot,Apache Struts 2,Struts,Apache Struts,Struts2,Struts 2,JSP,WebSphere,Rackspace,Lightsail,TensorFlow,Apache,httpd,OAuth,OAuth2,OAuth 2.0,OAuth 2,SOAP,MS Access,MariaDB,CodeIgniter,Swagger,MongoDB,CosmosDB,Cosmos DB,Kafka,Docker,MS Graph API,Graph API,GraphAPI,Flask,OpenAI,OpenAI API,CAS,SAML,OIDC,OpenID Connect,OpenID,GitLab CI/CD,Sentry,NoSQL,Express.js,ExpressJS,Objective-C,Gradle,Webpack,Firebase,Tomcat,Ajax,NDK,Android NDK,Android Studio,Xcode,Visual Studio,WebView,WKWebView,POSIX,curl,Docker Compose,Electron,SMTP,IMAP,POP3,GCC,HTTP,HTTP2,HTTP/2,HTTP3,HTTP/3,JNI,JDBC,MacOS,MinGW,Multithreading,mutex,network programming,socket programming,TCP socket,domain socket,socket,Unix socket,UDP,TCP,hole punching,NAT,Qt,QT,SDL,Service Worker,PWA,sh,Shell scripting,Linux programming,Regex,Regular expression,RegExp,thread safety,TWS,WebSocket,Wireshark,performance tuning,performance optimization,multithreaded programming,information security,InfoSec,Web technology,Web technologies,DB engine,database engine,DB engines,database engines,mobile development,web development,desktop development,AppScan,SAST,DAST,IAST,Win32'
if not skip_parsing:
 subprocess.run(['bin/python', 'main.py', text_html_from_xclip_file, fullkws], cwd=jppdir, check=True)
 field: dict = json.loads(Path(fields).read_text())
 company = field['company']
 title = field['title']
 recruiter = field['recruiter']
 postingsrc = field['postingsrc']
else:
 subprocess.run(['libreoffice', '--headless', '--convert-to', 'txt:Text', text_html_from_xclip_file], check=True, cwd=tdir)
 shutil.move(os.path.join(tdir, 'text_html_from_xclip.txt'), text_html_from_xclip_file+'.excerpt.txt')
 subprocess.run(['bin/python', 'main.py', text_html_from_xclip_file, fullkws, '-s'], cwd=jppdir, check=True)
 company = input('COMPANY:')
 if not company:
  company = subprocess.check_output(['xclip', '-o', '-selection', 'clipboard']).decode()
 title = input('TITLE:')
 if not title:
  title = subprocess.check_output(['xclip', '-o', '-selection', 'clipboard']).decode()
 recruiter = 'Recruiter'
 postingsrc = 'internet'

txtjobdesc = Path(text_html_from_xclip_file+'.excerpt.txt').read_text()
if 'cover letter' in txtjobdesc.lower():
 input('NOTE the posting contains "cover letter"!! (Take a look first and then enter to continue)')



kwsstr = Path(kwlst).read_text()
kws = kwsstr.split(', ')
if len(kws) != len(set(kws)):
 raise Exception('Duplicates in kws')
if 0 == len({'SQL','MySQL','SQLite','T-SQL','MS SQL','MSSQL','MS SQL Server','MSSQL Server','SQL Server','Oracle','PL/SQL','PostgreSQL','Postgres','MariaDB'}.intersection(kws)):
 kwsstr+=', SQL'
if 0 == len({'Flutter','Dart'}.intersection(kws)):
 kwsstr+=', Flutter'
if 0 == len({'JavaScript','JS'}.intersection(kws)):
 kwsstr+=', JavaScript'
if 0 == len({'Go','Golang'}.intersection(kws)):
 kwsstr+=', Go'
if 0 == len({'C++','C++11','C++14','C++17','C++20'}.intersection(kws)):
 kwsstr+=', C++'
if 0 == len({'Java','J2EE','Java EE'}.intersection(kws)):
 kwsstr+=', Java'
if 0 == len({'C#','.NET'}.intersection(kws)):
 kwsstr+=', C#'
#min_kws = ['Rust', 'Go', 'Java', 'C', 'C#', 'C++', 'JavaScript', 'Flutter', 'Cordova', 'SQL', 'Shell', 'AWK', 'Linux', 'Windows', 'Azure']
min_kws = ['Rust', 'C', 'Cordova', 'Shell', 'AWK', 'Linux', 'Windows', 'Azure']
if len(min_kws) != len(set(min_kws)):
 raise Exception('Duplicates in min_kws')
for kw in min_kws:
 if kw not in kws:
  kwsstr+=', '+kw
Path(os.path.join(tdir, 'techstub.txt')).write_text(kwsstr)
Path(os.path.join(tdir, 'summarystub.txt')).write_text(title+'. Results-oriented IT professional skilled in optimizing and creating systems for high user volumes. Proven expertise in enhancing mobile applications and delivering technological innovation. Ready to bring value to your team. Deep expertise in web technologies, database engines, information security, network programming, multithreaded programming, performance tuning, and cross-platform abstraction. 9+ years of experience in software development. Automation enthusiast, mobile developer. Rustacean, gopher, versatile programmer. ITIL® Foundation Certificate in IT Service Management. PRINCE2® Foundation Certificate in Project Management.\n')
Path(os.path.join(tdir, 'invisiblekeywordsuffix.txt')).write_text(re.sub('\\s+', ' ', txtjobdesc))

subprocess.run(['xclip', '-selection', 'clipboard'], input=company.encode(), check=True)
addrin: str = input('Clip the ADDRESS of the company OR enter any non-empty input to skip:')
if 'Recruiter' != recruiter:
 cl+=recruiter+'\n'
cl+=company+'\n'
if not addrin:
 addrin = subprocess.check_output(['xclip', '-o', '-selection', 'clipboard']).decode()
 addrin = addrin.strip()
 if len(addrin) < 150:
  cl+=addrin+'\n'
 else:
  print('Address INPUT is absurd! Too long! Address ignored.')
cl+='\nRe: '+title+' position\n\n'
cl+='Dear '+recruiter+',\n'

Path(text_html_from_xclip_file+'.title.txt').write_text(title)
Path(text_html_from_xclip_file+'.company.txt').write_text(company)
Path(text_html_from_xclip_file+'.postingsrc.txt').write_text(postingsrc)
Path(text_html_from_xclip_file+'.cl.begin.txt').write_text(cl)
Path(text_html_from_xclip_file+'.cl.end.txt').write_text('\nSincerely,\n\nEric C. Shu')

print('Starting to run the 1st slow part... (summary)')
subprocess.run(['bin/python', 'main.py', chatsummary], cwd=cthdir, check=True)
#? open the summary.full.txt in editor? but you do not want sudden popup, so you probably want a input() first, but input will block the following logic, thus still bad
print('Starting to run the 2nd slow part...')
subprocess.run(['bin/python', 'main.py', chatcl], cwd=cthdir, check=True)
subprocess.run(['libreoffice', '--headless', '--convert-to', 'pdf', outdocx], check=True, cwd=tdir)
shutil.move(outpdf, pdfrename)

while True:
 subprocess.run(['bin/python', 'main.py', os.path.join(tdir, 'resume.eric.c.shu.docx'), '--rep', rep, '--rep-json', repjson, '--generate-pdf', '--get-pdf-num-of-pages'], cwd=repdir, check=True)
 if input('ENTER empty input for re-generation of resume. ENTER any text to finalize.'):
  break
folder = datetime.now().strftime('%Y%m%d%H%M%S')
folder = 'archive/'+folder
subprocess.run('mkdir -p '+folder, cwd=tdir, shell=True, check=True)
subprocess.run('cp -p text_html_from_xclip.* '+folder, cwd=tdir, shell=True, check=True)
subprocess.run('cp -p invisiblekeywordsuffix.txt '+folder, cwd=tdir, shell=True, check=True)
subprocess.run('cp -p techstub.txt '+folder, cwd=tdir, shell=True, check=True)
subprocess.run('cp -p summarystub.txt '+folder, cwd=tdir, shell=True, check=True)
subprocess.run('cp -p summary.middle.txt '+folder, cwd=tdir, shell=True, check=True)
subprocess.run('cp -p summary.full.txt '+folder, cwd=tdir, shell=True, check=True)
subprocess.run('cp -p '+pdfrename+' '+folder, cwd=tdir, shell=True, check=True)
subprocess.run('cp -p '+outdocx+' '+folder, cwd=tdir, shell=True, check=True)
subprocess.run('cp -p resume.eric.c.shu_new.docx '+folder, cwd=tdir, shell=True, check=True)
subprocess.run('cp -p resume.eric.c.shu.pdf '+folder, cwd=tdir, shell=True, check=True)
print('DONE')

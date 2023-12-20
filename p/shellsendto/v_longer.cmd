@echo off
if [%1]==[] (start "" "C:\Program Files (x86)\Vim\vim90\gvim.exe" -n -i NONE -u NONE "+colo peachpuff" "+se guifont=Consolas:h11 go= lines=99 co=999 hid clipboard=unnamed hls ai enc=utf-8 nocompatible nu backspace=indent,eol,start" "+syntax on"
)else (start "" "C:\Program Files (x86)\Vim\vim90\gvim.exe" -n -i NONE -u NONE "+colo peachpuff" --remote-silent "+se guifont=Consolas:h11 go= lines=99 co=999 hid clipboard=unnamed hls ai enc=utf-8 nocompatible nu backspace=indent,eol,start" "+syntax on" %~s1)

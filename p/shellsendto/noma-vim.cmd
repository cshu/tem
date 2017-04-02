@REM filename is v, bc vi and vim are already taken, you need a distinct name
@start "" "C:\Program Files\Git\usr\bin\mintty.exe" -w max -e "C:\Program Files\Git\usr\bin\vim.exe" -n -i NONE --noplugin "+se title" "+se titlestring=%%{expand('%%:p:t')}\ %%{expand('%%t')}\ xxx\ NOT\ MODIFIABLE\ xxx" "+se noma" "+hi statusline ctermfg=darkcyan" %*

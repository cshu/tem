@REM filename is v, bc vi and vim are already taken, you need a distinct name
@start "" "C:\Program Files\Git\usr\bin\mintty.exe" -w max -e "C:\Program Files\Git\usr\bin\vim.exe" -n -i NONE --noplugin "+se title" "+se titlestring=%%{expand('%%:p:t')}\ %%{expand('%%t')}\ %%{&mod}" %*

@echo off
if [%1]==[] (start "" "C:\Program Files (x86)\Vim\vim80\gvim.exe" -n -i NONE --noplugin -u "C:\Program Files\Git\etc\vimrc" "+colo peachpuff" "+se go= gfn=Consolas:h11 lines=99 co=999 hid ff=unix"
)else (start "" "C:\Program Files (x86)\Vim\vim80\gvim.exe" -n -i NONE --noplugin -u "C:\Program Files\Git\etc\vimrc" "+colo peachpuff" "+se bh=wipe" --remote-silent "+se go= gfn=Consolas:h11 lines=99 co=999 hid ffs=unix,dos" %~s1)

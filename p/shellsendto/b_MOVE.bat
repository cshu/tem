:loop
if "%~1"=="" goto end
cd %1
move * E:\000FilesWithNoBackup
shift
goto loop
:end
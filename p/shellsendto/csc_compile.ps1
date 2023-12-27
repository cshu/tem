start -NoNewWindow "C:\Windows\Microsoft.NET\Framework\v4.0.30319\csc.exe" @('/t:exe','/out:out.exe',$args[0])
#[string[]]$argslist= '/t:exe','/out:out.exe',$args[0]
#$proc = [System.Diagnostics.Process]::Start("C:\Windows\Microsoft.NET\Framework\v4.0.30319\csc.exe", $argslist)
#$proc.WaitForExit()
#$proc.Dispose()
echo ALLDONE

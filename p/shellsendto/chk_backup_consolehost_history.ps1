$ErrorActionPreference = 'Stop';

$histsp = (Get-PSReadlineOption).historysavepath
$maxhistcount = (Get-PSReadlineOption).MaximumHistoryCount
echo histsp $histsp
echo maxhistcount $maxhistcount
$countthreshold = [Math]::DivRem($maxhistcount,2,[ref]$null)
echo countthreshold $countthreshold
$numoflines = cat $histsp | Measure-Object -Line
echo numoflines $numoflines
$newfile = rvpa ~/u/vcs/bb/homestuff/conhost_history
$dtstr = get-date -format 'yyyyddMMHHmmss'
$newfile = join-path $newfile ($dtstr + '.txt')
echo newfile $newfile
if ([System.IO.File]::Exists($newfile)) {
	echo 'ABORT CAUSED BY FILENAME CONFLICT'
	return
}
if ($numoflines.Lines -ge $countthreshold) {
	cp $histsp (join-path (rvpa ~) conhost_history.redundant_extra_backup.txt)
	cp $histsp $newfile
	if ([System.IO.File]::Exists($newfile)) {
		ni -path $histsp -force
	} else {
		echo 'THIS SHOULD BE UNREACHABLE'
	}
	echo COPIED
} else {
	echo NOOP
}
echo ALLDONE

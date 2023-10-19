#!/bin/sh
if [ ! -e ./bin/python ]; then
	echo ./bin/python not found
	exit 1
fi
./bin/python -m pip freeze > requirements.txt
if [ $? -eq 0 ]; then
	echo DONE
else
	echo FAILED
fi

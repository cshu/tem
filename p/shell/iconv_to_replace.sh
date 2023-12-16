#!/bin/sh
if [ $(uchardet "$2") = "UTF-8" ]; then
	mv "$2" /tmp/iconv_to_replace_tmp_file.txt
	iconv -f utf-8 -t "$1" -o "$2" /tmp/iconv_to_replace_tmp_file.txt
else
	echo 'Not utf-8'
	exit 1
fi

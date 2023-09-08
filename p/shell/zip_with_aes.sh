#!/bin/sh
echo 7za a -tzip -p -mem=AES256 "$1.zip" "$1"
7za a -tzip -p -mem=AES256 "$1.zip" "$1"

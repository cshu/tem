#!/bin/sh
for var in "$@"
do
    echo "$var" >> /dev/log.txt
done
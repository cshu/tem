#!/usr/bin/env bash
if [ "$#" -ne "2" ]; then
	echo must pass filename and passphrase
	exit 1
fi
basenm="$(basename "$1")"
if [ -z "$(echo "$basenm" | awk '/\./')" ]
then
	echo filename "$basenm" not ending with .gpg
	exit 1
fi
gpgext="$(echo "$basenm" | awk -F"." '{print $NF}')"
if [ "$gpgext" != "gpg" ]
then
	echo extension "$gpgext" not gpg
	exit 1
fi
originalnm="$(basename "$basenm" .gpg)"
if [ -z "$originalnm" ]
then
	echo filename is weird
	exit 1
fi
outnm="$(dirname "$1")/$originalnm"
echo gpg --batch --passphrase "$2" -o "$outnm" -d "$1"
gpg --batch --passphrase "$2" -o "$outnm" -d "$1"

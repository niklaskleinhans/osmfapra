#!/bin/sh
if [ "$(id -u)" != "0" ]; then
	echo "Sorry, but my bad script just works as root"
	exit 1
fi

sudo apt-get install libprotobuf-dev protobuf-compiler
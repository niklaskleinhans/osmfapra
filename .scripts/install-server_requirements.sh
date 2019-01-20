#!/bin/sh
if [ "$(id -u)" != "0" ]; then
	echo "Sorry, but my bad script just works as root"
	exit 1
fi

sudo apt install -y build-essential curl make cmake zlib1g-dev libboost-all-dev gcc-7 g++-7 git 
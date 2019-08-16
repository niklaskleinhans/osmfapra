#!/bin/sh

if [ "$(id -u)" != "0" ]; then
	echo "Sorry, but my bad script just works as root"
	exit 1
fi

echo "Download Nodejs"
curl -sL https://deb.nodesource.com/setup_12.x |  bash - && \
    sudo apt-get install -y nodejs \
    && echo "finished"
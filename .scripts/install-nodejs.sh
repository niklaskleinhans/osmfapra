#!/bin/sh

if [ "$(id -u)" != "0" ]; then
	echo "Sorry, but my bad script just works as root"
	exit 1
fi

echo "Download Nodejs"
curl -sL https://deb.nodesource.com/setup_10.x |  bash - && \
    sudo apt-get install -y nodejs \
    && echo "install angular cli now" \
    && sudo npm install -g @angular/cli \
    && echo "finished"
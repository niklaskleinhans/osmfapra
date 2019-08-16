#!/bin/sh

if [ "$(id -u)" != "0" ]; then
	echo "Sorry, but my bad script just works as root"
	exit 1
fi

echo "Add key"
echo 'deb http://www.rabbitmq.com/debian/ testing main' | sudo tee /etc/apt/sources.list.d/rabbitmq.list  && \
wget -O- https://www.rabbitmq.com/rabbitmq-release-signing-key.asc | sudo apt-key add - && \

echo "update packalist and install"
sudo apt-get update && sudo apt install -y rabbitmq-server
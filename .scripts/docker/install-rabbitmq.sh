#!/bin/sh

## Install RabbitMQ signing key
curl -fsSL https://github.com/rabbitmq/signing-keys/releases/download/2.0/rabbitmq-release-signing-key.asc | apt-key add -

## Install apt HTTPS transport
apt-get install apt-transport-https

## Add Bintray repositories that provision latest RabbitMQ and Erlang 21.x releases
tee /etc/apt/sources.list.d/bintray.rabbitmq.list <<EOF
deb https://dl.bintray.com/rabbitmq-erlang/debian bionic erlang-21.x
deb https://dl.bintray.com/rabbitmq/debian bionic main
EOF

## Update package indices
apt-get update -y

## Install rabbitmq-server and its dependencies
apt-get install rabbitmq-server -y --fix-missing
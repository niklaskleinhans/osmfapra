#!/bin/sh

echo "Download Nodejs"
curl -sL https://deb.nodesource.com/setup_12.x |  bash - && \
    apt-get install -y nodejs \
    && echo "finished"
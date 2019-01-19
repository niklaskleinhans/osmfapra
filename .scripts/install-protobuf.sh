#!/bin/sh
PROTOBUF_VERSION=3.6.1

if [ "$(id -u)" != "0" ]; then
	echo "Sorry, but my bad script just works as root"
	exit 1
fi

echo "Download protobuf"
curl -L -s https://github.com/protocolbuffers/protobuf/releases/download/v${PROTOBUF_VERSION}/protobuf-cpp-${PROTOBUF_VERSION}.tar.gz -o ./protobuf.tar.gz \
    && echo "Install protobuf now" \
    && tar -xzf ./protobuf.tar.gz -C ./ \
	&& rm -f ./protobuf.tar.gz \
	&& cd ./protobuf-${PROTOBUF_VERSION} \
    && ./configure \
	&& make \
	&& sudo make install \
    && cd .. \
    && echo "delete stuff we dont need anymore" \
    && rm -rf ./protobuf-${PROTOBUF_VERSION} \
    && echo "finished"


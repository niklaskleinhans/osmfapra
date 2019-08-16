#!/bin/sh
PROTOBUF_VERSION=3.6.1

echo "Download protobuf"
curl -L -s https://github.com/protocolbuffers/protobuf/releases/download/v${PROTOBUF_VERSION}/protobuf-cpp-${PROTOBUF_VERSION}.tar.gz -o ./protobuf.tar.gz \
    && echo "Install protobuf now" \
    && tar -xzf ./protobuf.tar.gz -C ./ \
	&& rm -f ./protobuf.tar.gz \
	&& cd ./protobuf-${PROTOBUF_VERSION} \
    && ./configure \
	&& make \
	&& make install \
    && ldconfig \
    && cd .. \
    && echo "delete stuff we dont need anymore" \
    && rm -rf ./protobuf-${PROTOBUF_VERSION} \
    && echo "finished"


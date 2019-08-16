FROM ubuntu:bionic

#FROM rabbitmq:3-management
#RUN rabbitmq-plugins enable --offline rabbitmq_mqtt rabbitmq_web_mqtt

RUN apt-get update

# Copy project
WORKDIR /usr/app/
COPY . .

# Install server Requirements
RUN .scripts/docker/install-server_requirements.sh

# Install Protobuf from sourcecode
RUN .scripts/docker/install-protobuf-sourcecode.sh

# Install Node.js
RUN .scripts/docker/install-nodejs.sh

# Install Rabbitmq
RUN .scripts/docker/install-rabbitmq.sh
RUN rabbitmq-plugins enable rabbitmq_management \
                            rabbitmq_web_mqtt \
                            rabbitmq_mqtt

# Configure Rabbitmq
RUN cp /usr/app/data/docker_rabbitmq.config /etc/rabbitmq/rabbitmq.config
RUN cp /usr/app/data/docker_rabbitmq-env.conf /etc/rabbitmq/rabbitmq-env.conf
RUN chown -R rabbitmq /usr/app/data/example.com.pem
RUN chown -R rabbitmq /usr/app/data/example.com-key.pem

# building the client
RUN cd client && \
    npm install && \
    npm rebuild node-sass && \
    npm run build && \
    cd ..

# building osmpbf
RUN cd server/libs/osmpbf && \
    git submodule init && \
    git submodule update --recursive --remote && \
    cd generics && git submodule init && cd .. && \
    git submodule update --recursive --remote && \
    mkdir -p build && \
    rm -f CMakeCache.txt && \
    cd build && rm -r * && cmake .. && make

# building application binary 
RUN cd /usr/app/server/src && make

EXPOSE 8080
EXPOSE 15672
EXPOSE 15673 
EXPOSE 15675 
EXPOSE 1883 

WORKDIR /usr/app/server/src

# Run Rabbitmq and app
CMD service rabbitmq-server start && \
    echo "Build APP" && \
    ./main.out ../../data/$PBFFILENAME 
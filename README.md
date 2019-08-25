# osmfapra
In Case of the practical Course "OpenStreetMaps" an Application to share the current position and calculating the remaining time to arrive was designed.

The clients communicate via the secured MQTT protocol. The bidirectional Dijkstra is used for Way calculation.

## How to Build
### [Option 1] Compile the Source
#### Requirements
- cmake >= 3.9
- protobuf >=3.6.1
- Boost >= 1.68.0
- Zlib >= 1.2.11
- make >=3.81
- gcc >= 7.3.0
- git 
- rabbitmq >= 3.7.17

In .scripts there are some example installation scripts. 
On Ubuntu 18.04 all requirements could be installed by running:
```
cd .scripts
sudo ./install-server_requirements.sh && \
sudo ./install-protobuf-sourcecode.sh && \
sudo ./install-rabbitmq.sh
```

For building the client some additional requirements are needed:
- nodejs >= 12.7.0
- npm >=6.9

#### Client
```
cd ./client/
npm install
npm run-script build
```

#### Server

##### lib/osmpbf
```
cd server/libs/osmpbf
git submodule init
git submodule update --recursive --remote
cd generics && git submodule init && cd ..
git submodule update --recursive --remote
rm -rf ./build && mkdir -p build
rm -f CMakeCache.txt
cd build && cmake .. # (for mac instead use cmake . -B ./build && cd build)
make
```

##### lib/Simple-Web-Server
Maybe done by step before
```
cd server/libs/Simple-Web-Server
git submodule init
git submodules update --recursive --remote
```

##### server
```
cd server/src/
make
```

##### Rabbitmq
1. generate certificate  
To make the communication work on mobile devices all of the communication must be secured. In the data folder there are some example keys
- example.com-key.pem (The key for rabbitmq-wss and webserver)
- example.com.pem (the cert for the rabbitmq-wss and webserver)

To generate certificates for development you can use mkcert (https://github.com/FiloSottile/mkcert). If you want to use the certificate in npm development server. Just generate a new file with (cat example.com.pem example.com-key.pem > server.pem and use this as certificate in webpack. Start development server with HTTPS=true npm start.


2. config rabbitmq
Make sure that rabbitmq is not running
```
sudo rabbitmqctl stop
```

edit config file in data/docker_rabbitmq.config and enter the correct certificate path. Then copy the config file:
```
cp ./data/docker_rabbitmq.config /etc/rabbitmq/rabbitmq.config
```

3. Start and install plugins
```
export PATH=$PATH:/usr/local/opt/rabbitmq/sbin
rabbitmq-plugins enable rabbitmq_management rabbitmq_web_mqtt rabbitmq_mqtt
rabbitmq-server
```

#### Run
```
cd server
./main.out --path-to-pbf--
```
### [Option 2] Use Docker
#### Requirements
- docker engine >= 19.03
#### Build
```
docker build -t osm .
```

#### run
```
docker run --name osmfapra -e PBFFILENAME=germany-latest.osm.pbf -p 8080:8080 -p 15672:15672 -p 15673:15673 osm
```
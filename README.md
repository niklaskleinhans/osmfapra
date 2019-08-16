# osmfapra
Fachpraktikum OpenStreetMaps


## Requirements
- cmake >= 3.9
- protobuf >=3.6.1
- Boost >= 1.68.0
- Zlib >= 1.2.11
- make >=3.81
- gcc >= 7.3.0
- git  

In .scripts there are some example installation scripts. For building the client some additional requirements are needed:
- nodejs >= 10.10.0
- angular CLI >= 7.2.1

## Build
### Client
```
cd ./client/
npm install
ng build
```

### Server

#### lib/osmpbf
```
cd ./libs/osmpbf
git submodule init
git submodules update --recursive --remote
cd generics && git submodule init && cd ..
git submodules update --recursive --remote
mkdir build
cd build && cmake .. # (for mac instead use cmake . -B ./build && cd build)
make
```

#### lib/Simple-Web-Server
```
cd ./libs/Simple-Web-Server
git submodule init
git submodules update --recursive --remote
git clone https://github.com/eidheim/Simple-Web-Server.git .
```

#### server
```
cd ./server/src/
make
```

## Run
```
./main.out --path-to-pbf--
```

##Docker
```
docker build -t osmfapra .
docker run --name osmfapra -e PBFFILENAME=germany-latest.osm.pbf -p 8080:8080 -p 15672:15672 -p 15673:15673 osm
```
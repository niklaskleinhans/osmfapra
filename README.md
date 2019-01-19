# osmfapra
Fachpraktikum osm Niklas Kleinhans

## Requirements
- protobuf >=3.6.1.3_1
- Boost >= 1.68.0
- Zlib >= 1.2.11

## Installation
### Build Requirements
#### osmpbf
```
# if you are using a repo clone
cd ./server/libs/osmpbf
git submodule init
git pull --recurse-submodules
mkdir build
cmake . -B ./build
cd build
make

# if you are using a download
cd ./server/libs/osmpbf
git clone https://github.com/inphos42/osmpbf.git .
mkdir build
cmake . -B ./build
cd build
make
```

#### Simple-Web-Server
```
# if you are using a repo clone
cd ./server/libs/Simple-Web-Server
git submodule init
git pull --recurse-submodules

# if you are using a download
cd ./server/libs/Simple-Web-Server
git clone https://github.com/eidheim/Simple-Web-Server.git .
```

### Build Client
```
Requirements and "How to build" is explained in 
cat ./client/Readme.md
```
### Build Server
```
cd ./server
make
```

## How to Start
```
./main.out --path-to-pbf--
```

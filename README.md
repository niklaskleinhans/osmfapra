# osmfapra
Fachpraktikum osm

## Requirements
- protobuf 
- Boost
- Zlib

## Installation
### osmpbf
```
cd ./server/libs/osmpbf
git submodule init
git pull --recurse-submodules
mkdir build
cmake . -B ./build
cd build
make
```

#!/bin/bash

osmdata="../../data/stuttgart-regbez-latest.osm.pbf"

if [ ! -z "$1" ]
    then 
        osmdata=$1
        echo "datafile: " $osmdata
fi

make -j4 && ./main.out $osmdata
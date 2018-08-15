#!/bin/bash

# This is for graphs in subdirs like:
# graphs/{graph10..graph100}/{g0..g100}
        
DIR=$1
echo graphs in $DIR

for d in $DIR/*; do
    ./a.out $d/*
    if [ 0 -ne $? ]; then
        break
    fi
done

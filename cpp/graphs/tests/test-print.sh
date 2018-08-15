#!/bin/bash

for f in tmp/rgraph/*; do
    diff <(cat $f) <(./a.out $f)
done

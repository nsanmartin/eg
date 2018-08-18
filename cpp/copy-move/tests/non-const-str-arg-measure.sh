#!/bin/bash


for ((i = 100; i < 15000; i += 100)); do
    ../build/non-const-str-arg-measure $i 65000
done

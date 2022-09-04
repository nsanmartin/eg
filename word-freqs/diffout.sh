#!/usr/bin/bash


BUILD=./build

runTestOut () {
    CMD1=$1
    CMD2=$2
    FILE=$3

    OUT=$(diff <($CMD1 < $FILE) <($CMD2 < $FILE))

    if [ -z $OUT ]; then
        printf "diff %s %s for file %-32s: Ok!\n" $CMD1 $CMD2 $FILE
    else
        MSG="diff $CMD1 $CMD2 for $FILE\t"
        >&2 echo Error: output does not match $MSG
        echo "$OUT"
    fi
}


if [ ! -z $1 ]; then
    for f in "$@"; do
        #make -B
        if [ $? -eq 0 ]; then
            runTestOut $BUILD/ver-fgets $BUILD/ver-words $f
        else
            echo Error
        fi
    done
else
    echo falta input
fi

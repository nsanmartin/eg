#!/bin/bash

CMD=../build/tprint
DIR=../tmp/rgraph
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

sp="/-\|"
sc=0
spin() {
   printf "\b${sp:sc++:1}"
   ((sc==${#sp})) && sc=0
}
endspin() {
   printf "\r%s\n" "$@"
}


check_graph() {
    f=$1
    if [ ! -d $f ]; then
        
        until DIFFOUT=$(diff -q <(cat $f) <($CMD $f)); do
            spin
        done
        endspin                                                                      


        # DIFFOUT=$(diff -q <(cat $f) <($CMD $f))
        if [ -z "$DIFFOUT" ]; then
            printf  "${f} ${GREEN}ok${NC}\n"
        else
        printf "${RED}error${NC}: file '$f' failed\n"
        return 1
        fi
    fi
}

export -f check_graph

if [ ! -z $1 ]; then DIR=$1; fi

if [ -f $CMD ]; then
    for f in ${DIR}/*; do
        check_graph $f
        if [ 1 -eq $? ]; then break; fi
    done
else
    echo $CMD not found. Try compiling
fi 

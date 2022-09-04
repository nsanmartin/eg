FILE=$1

BUILD=./build

run () {
    CMD=$1
    TIME="$({ time $CMD < $FILE | wc; } 2>&1)"

    printf "PROG %-20s %s " $CMD "|"
    echo $TIME
}

if [ ! -z $FILE ]; then
    echo "cat $FILE"
    for f in $BUILD/*; do
        run $f
    done
else
    echo falta input
fi


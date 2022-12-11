IN=$1

diff <(./build/wordhfreq $IN | sort) <(./build/wordhtablepp $IN | sort)


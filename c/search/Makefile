wordhfreq:
	gcc -Wall -O3 -o ./build/$@ -I./include word-freq.c ./src/*.c

wordhtablec:
	gcc -g -Wall  -o ./build/$@ word-htable.c

wordhtablepp:
	g++ -Wall -O3 -o ./build/$@ word-table.cpp


clean:
	find ./build -type f -delete


HashTable0:
	gcc -g -Wall -I../include -o ./build/$@ $@.c ../src/*.c


HashTable_word_freq_table:
	gcc -g -Wall -I../include -o ./build/$@ $@.c ../src/*.c


tsearch_word_freq_table:
	gcc -g -Wall -I../include -o ./build/$@ $@.c ../src/*.c

hsearch_word_freq_table:
	gcc -g -Wall -I../include -o ./build/$@ $@.c ../src/*.c

ppsearch:
	g++ -Wall -o ./build/$@ pphash.cpp

integ: HashTable_word_freq_table hsearch_word_freq_table tsearch_word_freq_table ppsearch

clean:
	find build -type f -delete



HashTable0:
	gcc -g -Wall -I../include -o ./build/$@ $@.c ../src/*.c


HashTable_word_freq_table:
	gcc -g -Wall -I../include -o ./build/$@ $@.c ../src/*.c


tsearch_word_freq_table:
	gcc -g -Wall -I../include -o ./build/$@ $@.c ../src/*.c

hsearch_word_freq_table:
	gcc -g -Wall -I../include -o ./build/$@ $@.c ../src/*.c

integ: HashTable_word_freq_table hsearch_word_freq_table tsearch_word_freq_table

clean:
	find build -type f -delete


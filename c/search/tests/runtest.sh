IN=$1
## make integ
diff <(./build/HashTable_word_freq_table $IN | sort) <(./build/hsearch_word_freq_table  $IN | sort)


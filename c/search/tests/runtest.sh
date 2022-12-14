IN=$1
## make integ
echo $1...
diff <(./build/HashTable_word_freq_table $IN | sort) <(./build/hsearch_word_freq_table  $IN | sort)
diff <(./build/ppsearch $IN | sort) <(./build/hsearch_word_freq_table  $IN | sort)


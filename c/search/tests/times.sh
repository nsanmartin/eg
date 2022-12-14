DATA=$1

echo $1
echo hsearch
time ./build/hsearch_word_freq_table $1 > /dev/null
echo HashTable
time ./build/HashTable_word_freq_table $1 > /dev/null
echo ppsearch
time ./build/ppsearch $1 > /dev/null


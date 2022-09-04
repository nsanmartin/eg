#include "words.h"

bool range_is_empty(Range r) ;
void range_skip_space_or_null(Range* r) ;
char* range_move_skip_word(Range* r) ;
char* find_next_space(Range r) ;
Word word_from_ptrs(char* beg, char* end) ;
Word buffer_read_next_word(Buffer* b) ;
int range_len(Range r) ;
Buffer empty_buffer_from_array(char* arr, int size) ;
bool buffer_is_empty(Buffer b) ;
char* copy_incomplete_word_to_beginning(WordStream* ws) ;
StreamStatus get_stream_status(WordStream s, int nread, int size) ;
void read_into_empty_buffer_from_file(WordStream* ws) ;

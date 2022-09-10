#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 20000
#define WORDS_PER_LINE 7
#define NWORDS 40000
#define MAX_WORDLEN 10


int main () {

    srand(time(NULL));

    const int nwords = NWORDS;
    const int words_per_line = WORDS_PER_LINE;
    const int max_word_len = MAX_WORDLEN;

    const int charset_size = '~' - '!';
    const int min_char = '!';


    char buffer[(1 + words_per_line) * max_word_len + 1];

    const int nlines = nwords / words_per_line;

    for (int l = 0; l < nlines; ++l) {

        int lix = 0;
        for (int w = 0; w < words_per_line; ++w) {
            for(int wlen = 1 + rand() % max_word_len; wlen > 0; --wlen) {
                buffer[lix++] = rand() % charset_size + min_char; 
            }
            buffer[lix++] = ' ';
        }
        buffer[lix] = '\0';
        printf("%s\n", buffer);
    }
}

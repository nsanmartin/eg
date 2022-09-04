#include "word-freqs.h"

#define BUFFER_SIZE 80000

int main () {
    char buffer[BUFFER_SIZE];
    WordStream ws = make_word_stream(STDIN_FILENO, buffer, BUFFER_SIZE);

    while (ws.status == HasNext) {
        Word w = get_next_word(&ws);
        //if (ws.status != HasNext) { break; }
        //if (w.size == 0) { break; }
        printf("%s\n", w.cstr);
        //printf("%.*s\n", w.size, w.cstr);
    }


}



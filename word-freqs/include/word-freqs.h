#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


typedef enum { Empty, HasNext, End, Error } StreamStatus;

typedef enum { BufferHasData, BufferEmpty, BufferError } BufferStatus;


typedef struct {
    char* cstr;
    int size;
} Word;


typedef struct {
    char* beg;
    char* end;
} Range;

typedef struct {
    char* data;
    const int size;
    Range readable;
    Range incomplete_word;
} Buffer;


typedef struct {
    int fd;
    Buffer buffer;
    Word next;
    StreamStatus status;
    bool file_read;
} WordStream;


WordStream make_word_stream(int fd, char* arr, int size) ;
Word get_next_word(WordStream* ws) ;

#ifndef __WORD_FREQS_H_
#define __WORD_FREQS_H_

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


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
bool word_eq(Word v, Word w) ;
Word word_from_range(Range r) ;
//int range_len(Range r) ;
#endif

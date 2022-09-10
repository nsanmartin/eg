#ifndef __DO_WORDS_
#define __DO_WORDS_

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "lambda.h"


typedef struct {
    char* beg;
    char* end;
} Range;

typedef struct {
    Range range;
    bool end_of_line;
} Line;


void do_words(FILE* stream, Lambda* lam)  ;

bool end_of_line(Line ln) ; 
int range_len(Range r) ;
bool range_is_empty(Range r) ;
bool range_has_next(Range r) ;
bool subrange_has_word(Range r, char* end) ;
char* first_not_space(Range r) ;
Range range_get_next_word(Range r) ;
int copy_range(Range r, char* dest) ;

#endif

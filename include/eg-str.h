#ifndef __EG_STR_H_
#define __EG_STR_H_

#include <stdbool.h>
#include <string.h>

#include "eg-result.h"

#define strFromLit(CSTR) ({ Str rv = { .cstr = CSTR, .len = LEN(CSTR) }; rv; })

typedef struct {
    size_t len;
    char* cstr;
} Str;


inline bool strEq(Str x, Str y) { return x.len == y.len && strcmp(x.cstr, y.cstr) == 0; }
void strCopy(Str s, Result res) ;

#endif



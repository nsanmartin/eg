#ifndef __EG_RESULT_H_
#define __EG_RESULT_H_

#include <stdbool.h>

#include "eg-str.h"

typedef struct {
    char* msg;
} Error;

typedef struct {
    void* ok;
    bool err;
} Result;

#endif


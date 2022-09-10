#ifndef __EG_RESULT_H_
#define __EG_RESULT_H_

#include <stdbool.h>


typedef struct {
    char* msg;
} Error;

typedef struct {
    bool err;
    void* ok;
} Result;

#endif


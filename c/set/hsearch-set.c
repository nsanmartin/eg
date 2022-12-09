#define _GNU_SOURCE

#include <search.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
        struct hsearch_data* htab;
        int sz;
        int cap;
        char buf[5];
        int* elems;
} SetInt;


int setIntInit(SetInt* set, int initial_capacity) {
        set->elems = malloc(sizeof(int) * initial_capacity);
        if (!set->elems)
                return -1;
        set->cap = initial_capacity;
        set->sz = 0;

        int nel = 1 + (initial_capacity * 5) / 4;
        set->htab = calloc(1, sizeof(struct hsearch_data));
        if (!set->htab) {
            free (set->elems);
            return -1;
        }
        int error = hcreate_r(nel, set->htab) == 0;
        if (error) {
            free(set->elems);
            free(set->htab);
        }
        return error; 
}

char* setIntIntToStr(SetInt* s, int el) {
    s->buf[4] = '\0';
    for (int i = 0; i < 4; ++i) {
        s->buf[i] = ((char*)&el)[i];
    }
    return s->buf;
}


int setIntInsert(SetInt* s, int el) {
    ENTRY e = { .key = setIntIntToStr(s, el) };
    ENTRY* r;
    int error = hsearch_r(e, ENTER, &r, s->htab) == 0;
    if (error)
        return error; 

    if (!r)
        return -1;

    return 0;
}

int setIntContains(SetInt* s, int el) {
    ENTRY e = { .key = setIntIntToStr(s, el) };
    ENTRY* r;
    hsearch_r(e, FIND, &r, s->htab);
    return r != NULL;
}

int main(int argc, char* argv[]) {
    SetInt s;
    setIntInit(&s, 10);
    setIntInsert(&s, 1);
    setIntInsert(&s, 2);
    if (setIntContains(&s, 1)) {
        printf("1 is\n");
    } else {
        printf("1 is not\n");
    }

    if (setIntContains(&s, 12345)) {
        printf("12345 is\n");
    } else {
        printf("12345 is not\n");
    }
}

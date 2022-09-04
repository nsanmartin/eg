
void print_range(Range r, char* msg) {
    int len =r.end - r.beg; //TODO:check overflow
    printf("%s\nrange: '%.*s', len: %d.\n", msg, len, r.beg, len);
    for(char* it = r.beg; it < r.end; ++it) {
        printf("'%c' (%d), ", *it, *it);
    }
    puts("");
}


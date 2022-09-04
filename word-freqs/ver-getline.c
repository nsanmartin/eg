#include <stdio.h>

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "word-freqs.h"

#define BUFFER_SIZE 100

#define panic(msg) \
    fprintf(stderr, "words: %s\n", msg); \
    exit(1)

inline bool is_space_or_null(char c) {
    return isspace(c) || c == '\0';
}

int main()
{
  int nread;
  size_t nbytes;
  char *buffer = (char *) malloc (BUFFER_SIZE);

  while((nread = getdelim (&buffer, &nbytes, ' ', stdin)) > 0) {
      char* beg = buffer;
      char* end = buffer;
      while (end < buffer + nread) {
          //skip space
          while(is_space_or_null(*beg) && beg < buffer + nread) {
              ++beg;
          }
          end = beg;
          while(!is_space_or_null(*end) && beg < buffer + nread) {
              ++end;
          }

          if (beg < end) {
              printf("%.*s\n", (int)(end-beg), beg); // TODO:check overflow
          }
          beg = end;
      }
  };


  return 0;
}

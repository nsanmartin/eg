#include <iostream>
#include <string>

#include <cstring>
static const int BUFSZ = 65536;
static const int TIMES = 65536;

void print_usage(char * program) {
     std::cout << "use: " << program << " [copy, ref]"
               << std::endl;
}

void fit_ascii(char * a, int n) {
    for (int i = 0; i < n; i++) {
          unsigned char d = 0x20 + (a[i] & 0x3f);
          a[i] = d;
     }
}

void copy_string(std::string s, int times) {
     if (times < 0)
          return;
     copy_string(s, times - 1);
}

void ref_string(std::string& s, int times) {
     if (times < 0)
          return;
     ref_string(s, times - 1);
}

int main (int argc, char ** argv) {
     
     char array[BUFSZ];
     fit_ascii(array, BUFSZ);
     std::string s(array);

     if (argc == 1) {
          print_usage(argv[0]);
     } else if  (strcmp(argv[1], "copy") == 0) {
          copy_string(s,TIMES);
     } else if (strcmp(argv[1], "ref") == 0) {
          ref_string(s, TIMES);
     } else {
          std::cerr << "unknown command " << argv[1]
                    << std::endl;
          exit(1);
     }
     
     std::cout << TIMES << " times "
               << "for buffer of size "<< BUFSZ
               << std::endl;
     
}

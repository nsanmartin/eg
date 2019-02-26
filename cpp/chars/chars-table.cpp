#include <iostream>
#include <fstream>

#include <cstring>

void print_table(unsigned * table, int n) {
    unsigned count = 0;
    for (int i = 0; i < n; i++) {
        if (table[i]) {
            count++;
            char ch{(char)i};
            std::cout << ch << "\t" << i << "\t" << table[i] <<
                std::endl;
        }
    }
    std::cout << count << " chars" << std::endl;
}


void chars_table(char * filename) {
    char ch;
    unsigned table[256] = {};
    std::fstream f(filename);
    while ( f >> std::noskipws >> ch ) {
        table[ch]++;
    }
    print_table(table, 256);
    
    
}


int main(int argc, char ** argv) {
    for (int i = 1; i < argc; i++) {
        chars_table(argv[i]);
    }
}

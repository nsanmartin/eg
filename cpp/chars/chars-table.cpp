#include <iostream>
#include <fstream>
#include <array>
#include <string>

using CharTable = std::array<unsigned,256>;
using TableIt = CharTable::iterator;

void print(TableIt begin, TableIt end) {
    unsigned count = 0;
    auto it = begin;
    for (; it != end; ++it) {
        if (*it) {
            ++count;
            auto i = std::distance(begin, it);
            char ch{(char) i};
            std::cout << ch << "\t" << i << "\t" << *it
                      << '\n';

        }
    }
    std::cout << count << " chars\n";
}


std::array<unsigned, 256> chars_table(const std::string& filename) {
    char ch;

    std::array<unsigned, 256> table{};
    std::fstream f(filename);
    while ( f >> std::noskipws >> ch ) {
        table[ch]++;
    }

    return table;
    
}


int main(int argc, char ** argv) {

    if (argc == 1) {
        std::cout << "use: " << argv[0] << " FILE [FILE...]\n";
        return 0;
    }
    
    for (int i = 1; i < argc; i++) {
        auto table = chars_table(argv[i]);
        print (table.begin(), table.end());
    }
}

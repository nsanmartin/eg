#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <fstream>

using std::cin;
using std::cout;
using std::unordered_map;
using std::map;
using std::string;
using std::ifstream;

int main(int argc, char* argv[]) {

    if (argc < 2) 
          printf("Uso: %s FILE \n", argv[0]);

    unordered_map<string,int> table;
    string word;

    ifstream file{argv[1]};

    while (file >> word) {
        ++table[word];
    }


    for (auto& p:table) {
        cout << p.first << ": " << p.second << '\n';
    }
}

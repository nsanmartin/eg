#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

int main (int argc, char* argv[]) {
    if (argc < 2) 
         printf("Uso: %s FILE [FILE ...]\n", argv[0]);

    ifstream file(argv[1]);
    string s;
    unordered_map<string, long> table;


    while(file >> s) {
        ++table[s];
    }

    for (auto& p: table) {
        cout << p.first << ": " << p.second << '\n';
    }
}

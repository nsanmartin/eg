#include <iostream>
#include <string>
#include <unordered_map>
#include <map>

using std::cin;
using std::cout;
using std::unordered_map;
using std::map;
using std::string;

int main() {
    //map<string,int> table;
    unordered_map<string,int> table;
    string word;

    while (cin >> word) {
        ++table[word];
    }

    for (auto& p:table) {
        cout << p.first << ": " << p.second << '\n';
    }
}

#include <string>
#include <iostream>
#include <unordered_map>
#include <map>

int main() {
    std::string word;
    std::unordered_map<std::string, long> table{};

    while (std::cin >> word) {
        //std::cout << word << '\n';
        table[word]++;
    }

    //std::map<long, std::string> sorted{};
    for (auto p: table) {
        //sorted[p.second] = p.first;
        std::cout << p.first << ": " << p.second << '\n';
    }

    //for (auto p: sorted) {
    //    std::cout << p.second << ": " << p.first << '\n';
    //}
}

#include <iostream>
#include <vector>

#include "binary-search.hpp"
int main () {
    std::vector<int>array {0, 0, 1, 1, 2, 3, 3, 4, 8 };

    std::cout << "array: ( ";
    for (auto& x : array) { std::cout << x << " "; }
    std::cout << ")" << std::endl;
    for (int key = -2; key < static_cast<int>(array.size()) + 2;
         key++) {
        size_t res { binary_search(array, key) };
    
        std::cout << "search: " << key <<  " found: " << res
                  << ": " << array[res] << std::endl;
    }
}

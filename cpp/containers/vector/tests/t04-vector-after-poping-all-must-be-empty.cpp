#include <iostream>
#include "tests.hpp"

int main(int argc, char** argv) {

    eg::vector<int> v{};
    int times = 1024;

    for (int i = 0 ; i < times; ++i) { v.push_back(i); }
    for (int i = 0 ; i < times; ++i) { v.pop_back(); }
    
    eg::tests::test_assert(v.empty(), argv[0]);
}

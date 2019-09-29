#include <iostream>
#include "tests.hpp"

int main(int argc, char** argv) {

    eg::vector<int> v{};
    std::vector<int> stdv{};

    for (int i = -64; i < 1024; i++) {
         v.push_back(i);
         stdv.push_back(i);
    }

    eg::tests::test_equal(stdv, v, argv[0]);
}

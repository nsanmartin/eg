#include <iostream>
#include "tests.hpp"

int main(int argc, char** argv) {

    eg::vector<int> v{};
    eg::tests::test_assert(v.begin() == v.end(), argv[0]);
    v.push_back(0);
    v.pop_back();
    eg::tests::test_assert(v.begin() == v.end(), argv[0]);

}

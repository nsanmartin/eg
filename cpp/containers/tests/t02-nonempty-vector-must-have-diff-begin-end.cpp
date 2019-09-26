#include <iostream>
#include "tests.hpp"

int main(int argc, char** argv) {

    eg::vector<int> v{};
    v.push_back(1);
    eg::tests::test_condition(v.begin() != v.end(), argv[0]);
}

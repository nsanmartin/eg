#include <iostream>
#include "tests.hpp"

int main(int argc, char** argv) {

    eg::vector<int> v{};
    eg::tests::test_condition(v.begin() == v.end(), argv[0]);
}

#include <iostream>
#include <egtests.hpp>
#include <egvector.hpp>


int main(int argc, char** argv) {

    eg::vector<int> v{};
    v.push_back(1);
    eg::tests::test_assert(v.begin() != v.end(), argv[0]);
}

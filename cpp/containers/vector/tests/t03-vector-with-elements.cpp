#include <iostream>
#include <vector>
#include <egtests.hpp>
#include <egvector.hpp>

int main(int argc, char** argv) {

    eg::vector<int> v{};
    std::vector<int> stdv{};

    for (int i = -64; i < 1024; i++) {
         v.push_back(i);
         stdv.push_back(i);
    }

    eg::tests::test_assert_same_elems(stdv, v, argv[0]);
}

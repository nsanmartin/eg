#include <iostream>
#include <egtests.hpp>
#include <egvector.hpp>

int main(int argc, char** argv) {

    eg::vector<int> v{};
    int num_0 = 1024;
    v.push_back(num_0);
    eg::tests::test_assert(v.back() == num_0, argv[0]);

    int num_1 = 0x43;
    v.push_back(num_1);
    eg::tests::test_assert(v.back() == num_1, argv[0]);

    v.pop_back();
    eg::tests::test_assert(v.back() == num_0, argv[0]);

}

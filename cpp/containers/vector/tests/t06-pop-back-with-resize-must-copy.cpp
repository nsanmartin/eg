#include <iostream>
#include <vector>
#include <egtests.hpp>
#include <egvector.hpp>

int main(int argc, char** argv) {

    eg::vector<int> v{};
    std::vector<int> w{};
    
    for (int i = 0; i < 32; ++i) {
        v.push_back(i);
        w.push_back(i);
    }

    for (int i = 0; i < 1024; ++i) {
        v.push_back(13);
    }

    for (int i = 0; i < 1024; ++i) {
        v.pop_back();
    }
    
    eg::tests::test_assert_same_elems(v, w, argv[0]);

}

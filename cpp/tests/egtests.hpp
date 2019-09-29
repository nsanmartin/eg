#ifndef __EG_TESTS_
#define __EG_TESTS_

#include <iostream>
#include <string>

namespace eg {
namespace tests {

    
    void
    test_assert (bool condition, const std::string& testname)
    {
        std::cout << testname;
        if ( condition ) {
            std::cout << " Ok.\n";
        } else {
            std::cerr << " error.\n";
            std::exit(1);
        }
    }

    template<typename it_type_a, typename it_type_b>
    bool test_cmp_ranges(it_type_a begin_a, it_type_a end_a, it_type_b begin_b, it_type_b end_b) {
        auto ita = begin_a;
        auto itb = begin_b;
        for (; ita != end_a && itb != end_b; ++ita, ++itb) {
                if (*ita != *itb) { return false; }
        }
        return ita == end_a && itb == end_b;
    }

    template<typename ContainerA, typename ContainerB>
    void test_assert_same_elems(ContainerA& a, ContainerB& b, const std::string& testname) {
        test_assert(test_cmp_ranges(a.begin(), a.end(), b.begin(), b.end()),
                    testname);
    }

}
}


#endif // __EG_TESTS_

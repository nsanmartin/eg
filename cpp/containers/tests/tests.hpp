#ifndef __EG_CONTAINER_TESTS_
#define __EG_CONTAINER_TESTS_

#include <string>
#include <vector>
#include <eg/cpp/containers/vector.hpp>

namespace eg { namespace tests {

        void test_condition (bool condition, const std::string& testname) {
            std::cout << testname;
            if ( condition ) {
                std::cout << " Ok.\n";
            } else {
                std::cerr << " error.\n";
                std::exit(1);
            }
        }

        
        template<typename T>
        bool are_equal(const std::vector<T>& std_vector, const eg::vector<T>& eg_vector) {
            auto it_std = std_vector.begin();
            auto it_eg = eg_vector.begin();
            for (;it_std != std_vector.end() && it_eg != eg_vector.end(); ++it_std, ++it_eg) {
                if (*it_std != *it_eg) { return false; }
            }
            return it_std == std_vector.end() && it_eg == eg_vector.end();
        }

        
        template<typename T>
        void test_equal (const std::vector<T>& std_vector, const eg::vector<T>& eg_vector, const std::string& testname) {
            test_condition (eg::tests::are_equal(std_vector, eg_vector), testname);
        }
        
        template<typename T>
        void test_equal(const eg::vector<T>& eg_vector, const std::vector<T>& std_vector, const std::string& testname) {
            test_equal(std_vector, eg_vector, testname);
        }


    }
}
#endif

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
}


#endif // __EG_TESTS_

#include <type_traits>
#include <array>
#include <iostream>
#include "inner-prod.h"

template<typename Iter, typename SizeType>
auto inner_prod_(Iter u, Iter v, SizeType n) {

    typename std::iterator_traits<Iter>::value_type res{};
    for (SizeType i = 0; i < n; ++i) {
        res += *(u+i) * *(v+i);
    }
    return res;
}

float inner_prod_arrays(std::array<float, 4> u,
                  std::array<float, 4> v, unsigned n) {
    float res{};
    for (int i = 0; i < n; ++i) {
        res += u[i] * v[i];
    }
    return res;
}

int main () {
    constexpr std::array<float, 4> u {10.21, 2.3, 6.1, 2.3};
    constexpr std::array<float, 4> v {1, 21.3, 6.1, 1.3};


    auto res_static = inner_prod<4u>::sum(u.begin(), v.begin(),
                                          0.0f);
    
    auto res_nonstatic_array = inner_prod_arrays(u, v, u.size());
    auto res_nonstatic_ = inner_prod_(u.begin(), v.begin(), u.size());
    
    std::cout << "static: " << res_static << '\n'
              << "non static array: " << res_nonstatic_array << '\n'
              << "non static: " << res_nonstatic_ << '\n'
        ;

}

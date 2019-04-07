#include <iostream>
#include <vector>
#include <iterator>
#include "binary-search.hpp"
#include <random>
#include <algorithm>

template<typename I>
void print_array(I it, const I end) {
    using namespace std;
    cout << "array: ( ";
    while (it != end) {
        cout << *it << " ";
        it = next(it);
    }
    cout << ")" << endl;
}

template<typename I>
void print_indexes(I it, const I end) {
    using namespace std;
    cout << "array: ( ";
    int indx{};
    while (it != end) {
        cout << indx++ << " ";
        it = next(it);
    }
    cout << ")" << endl;
}


int main () {
    std::random_device random_device;

    std::mt19937 mersenne_engine {random_device()};
    std::uniform_int_distribution<> distribution {0, 16};

    auto gen = [&distribution, &mersenne_engine]() {
        return distribution(mersenne_engine);
    };

    auto fill_vector_with_random_numbers = [&gen](std::vector<int>& vector) {
        std::generate(std::begin(vector), std::end(vector), gen);
    };


    size_t n{9};
    std::vector<int> array(n);
    fill_vector_with_random_numbers(array);
    std::sort (array.begin(), array.end(), [](int x, int y) {return y < x;});

    print_array(array.begin(), array.end());
    print_indexes(array.begin(), array.end());
    std::cout << "search-for   bin-indx   bin-val  lb-dist   ln-val"
              << std::endl;
    
    for (int key = -2; key < static_cast<int>(array.size()) + 2;
         key++) {

        size_t res { binary_search_decreasing(array, key) };
        auto res_lb = std::lower_bound (
            array.begin(), array.end(), key,
            [](int x, int y) { return y < x; }
            );
        std::cout << "    " << key << "\t\t"
                  << res << "\t   " << array[res] << "\t\t"
                  << std::distance(array.begin(), res_lb)
                  << "\t" << *res_lb
                  << std::endl;
    }
}

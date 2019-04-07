#include <vector>
#include <cassert>
#include <iterator>
#include <iostream>

template <typename I, // forward iterator
          typename T>
I bin_lower_bound(I f, I l, const T& v) {
    while (f != l) {
        auto m = std::next(f, std::distance(f, l) / 2);

        if (*m < v) { f = std::next(m); }
        else l = m;
    }
    return f;
}

template <typename T>
size_t binary_search_leftmost(const std::vector<T> array, const  T& key) {
    assert (array.size() >= 1);    
    size_t low {0};
    size_t high{array.size() - 1};

    while (low < high - 1) {
        size_t med {low + (high - low) / 2};
        if (array[med] >= key) { high = med; }
        else { low = med;  }
    }

    if (array[low] >= key) { return low; }
    return high;
}

template <typename T>
size_t
binary_search_decreasing(const std::vector<T> array, const  T& key) {
    assert (array.size() > 0);    
    size_t low {0};
    size_t high{array.size() - 1};

    while (low < high - 1) {
        size_t med {low + (high - low) / 2};
        if ( array[med] < key) { high = med; }
        else { low = med;  }
    }
    
    if ( array[low] > key) { return high; }
    else { return low; }
    
    return 0;
}

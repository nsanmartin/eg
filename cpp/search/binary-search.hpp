#include <vector>
#include <cassert>

template <typename T>
size_t binary_search(const std::vector<T> array, const  T& key) {
    assert (array.size() >= 0);    
    size_t low {0};
    size_t high{array.size() - 1};

    while (low < high - 1) {
        size_t med {low + (high - low) / 2};
        if ( array[med] >= key) { high = med; }
        else { low = med;  }
    }
    
    if ( array[low] >= key) { return low; }
    else { return high; }
    
    return 0;
}

#include <iostream>
#include <vector>

// class PascalTriangle {
//     std::vector<unsigned> _prev;
//     std::vector<unsigned> _last;

// public:
//     PascalTriangle(unsigned n) : _prev{n}, _last{n} {
//         _prev[0] = 1;
//     }

//     void compute(unsigned n);
// };


// void PascalTriangle::compute(unsigned n) {
    
//     for (int i = 1; i < n; ++i) {
        
//     }
// }

size_t idx(size_t n, size_t i, size_t j) { return i*n + j; }

void set(std::vector<unsigned>&v, size_t i, size_t j, unsigned x) {
    v.at(idx(v.size(), i, j)) = x;
}

unsigned get(std::vector<unsigned>& v, size_t i, size_t j) {
    return v.at(idx(v.size(), i, j));
}


unsigned choose(unsigned n, unsigned k) {
    std::vector<unsigned> C{(n+1) * (n+1)};
    
    C.at(0) = 1;
    for (int i = 1; i <= n; ++i) {
        set(C,n,0, 1);
        set(C,n,n, 1);

        for (int k = 1; k < i; ++k)
            set(C, n, k, get(C,n - 1, k - 1) + get(C, n - 1, k));
    }

    return get(C,n,k);
}

int main (int argc, char* argv[]) {
    if (argc != 3) { std::cout << "usage: ./" << argv[0] << " NUM NUM\n"; }
    else {

        std::cout << choose(std::atoi(argv[1]), std::atoi(argv[2])) << '\n';
    }
}

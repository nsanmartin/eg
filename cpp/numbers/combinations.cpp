#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
#include <unistd.h>

class Combinations {
    int k;
    std::vector<int> from;
    std::string elems;
    std::vector<int> comb;
public:
    Combinations(int n, int k) : k{k}, from(n), elems{}, comb{}{
        assert(k <= n);
        std::iota(from.begin(), from.end(), 0);
        comb.reserve(k);
    }

    Combinations(std::string elems, int k)
        : k{k}, from(elems.size()), elems{elems}, comb{} {
            assert(k <= elems.size());
            std::iota(from.begin(), from.end(), 0);
            comb.reserve(k);
    }

    void print_combinations(int index, int tomados);
    void print_comb() const;
};

void Combinations::print_comb() const {
    if (elems.size() == from.size()) {
        for (auto& index: comb)
            std::cout << elems[index];
        std::cout << "\n";
        
    } else {
        for (auto& x: comb) std::cout << x << " ";
        std::cout << "\n";
    }
}

void Combinations::print_combinations(int index, int tomados) {
    if (tomados == k) {
        print_comb();
    } else {
        for (int i = index; i < from.size(); ++i) {
            comb.push_back(from[i]);
            print_combinations(i + 1, tomados + 1);
            comb.pop_back();
        }
        
    }
}


int main(int argc, char** argv) {
    char c;
    bool numeric_param{false};
    while ((c = getopt(argc, argv, "n")) != -1) {
        switch (c) {
        case 'n':
            numeric_param = true;
            break;
        case '?':
            std::cerr << "Opcion desconocida"
                      <<  optopt;
            return 1;
        default:
            abort ();
	
        }
    }
    
    if (argc - optind != 2) {
        std::cout << "./prog  <string>  <k> \n"
                  << "./prog -s <n>  <k> \n";
    } else {

        int k{std::atoi(argv[optind+1])};

        if (numeric_param) {
            int n{std::atoi(argv[optind])};
            Combinations combs(n, k);
            combs.print_combinations(0, 0);
        } else {
            std::string string{argv[optind]};
            Combinations combs(string, k);
            combs.print_combinations(0, 0);

        }
    }
}

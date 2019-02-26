#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <random>


int main(int arc, char ** argv) {

    std::vector<int> ns;
    std::transform(argv + 1, argv + arc, std::back_inserter(ns), [] (char * str) {
            return std::stoul(str, 0, 10);
        });

    if (ns.size() == 0) { ns.push_back(33); }
    std::random_device random_device;

    std::mt19937 mersenne_engine {random_device()};
    std::uniform_real_distribution<double> distribution {0.0, 1.0};

    auto gen = [&distribution, &mersenne_engine]() {
        return distribution(mersenne_engine);
    };

    auto print_n_random_numbers = [&gen](int n) {
        std::vector<double> vector(n);
        std::generate(std::begin(vector), std::end(vector), gen);
        for (auto x : vector) {  std::cout << x << std::endl; }
    };

    std::cout.precision(std::numeric_limits<double>::max_digits10);
    for (int n : ns) {
        std::cout << "Generating " << n << " random doubles in [0, 1]" << std::endl;
        print_n_random_numbers(n);
    }
    // std::vector<double> vector(n);
    // std::generate(std::begin(vector), std::end(vector), gen);


}



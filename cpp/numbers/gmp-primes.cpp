#include <gmpxx.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Primality {
    std::vector<mpz_class> primes;
    void expand_bounded(const mpz_class& n);
    void expand_until(const mpz_class& n);
    void expand_times(int n);

    mpz_class next_prime();
public:
    Primality() : primes{mpz_class{2}, mpz_class{3}} {}
    Primality(int n) : Primality{} { expand_times(n); }

    bool is_prime(const mpz_class& n);
    bool is_prime(long unsigned n);
    bool is_prime(std::string n);

    void print_primes() const;
    const mpz_class& last_prime() const { return primes.back(); }
};

        
bool Primality::is_prime(const mpz_class& n) {
    expand_bounded(n);
    for (auto& p : primes) {
        if (p * p > n) { return true; }
        if (mpz_divisible_p(n.get_mpz_t(), p.get_mpz_t())) { return false; }
    }
    return true;
}

bool Primality::is_prime(long unsigned n) { return is_prime(mpz_class{n});}

bool Primality::is_prime(std::string n) {
    return is_prime(mpz_class{n});
}


void Primality::print_primes() const {
    for (auto& p : primes) { std::cout << p.get_str(10) << "\n"; }
}

mpz_class Primality::next_prime() {
    mpz_class next{last_prime() + 2};
    while (!is_prime(next)) {
        next += 2;
    }
    return next;
}


void Primality::expand_times(int n) {
    for (int i = 0; i < n; i++) { primes.push_back(next_prime()); }
}

void Primality::expand_until(const mpz_class& n) {
    while (last_prime() < n) { primes.push_back(next_prime()); }
}

void Primality::expand_bounded(const mpz_class& n) {
    while (last_prime() * last_prime() < n) {primes.push_back(next_prime());}
}

int main (int argc, char** argv) {
    if (argc == 1) { return 0; }

    std::vector<std::string> args(argv + 1, argv + argc);

    Primality primality{};

    for (auto& n : args) {
        if (primality.is_prime(n)) {
            std::cout << n << "\n";
        }
    }
    
    return 0;

                                              
}

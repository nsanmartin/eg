#include <iostream>

// from cppreference
template<typename ...Args>
void printer(Args&&... args) {
    (std::cout << ... << args) << '\n';
}
// from so
template <class... Ts>
void print_all(Ts const&... args) {
    (void(std::cout << args), ...);
    std::cout << '\n';
}


int main () {

    printer(1, 4.6f, "fara&%");
    print_all(2, 3.5f, ")&/houih");
}

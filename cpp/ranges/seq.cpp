#include <vector>
#include <ranges>
#include <iostream>

int main()
{
    auto filter_fun = [](int i){ return i % 7 == 1; };
    auto square = [](int i) { return i * i; };

    auto rng = std::views::iota(1, 100)
        | std::views::filter(filter_fun)
        | std::views::transform(square);

    for (auto e: rng) {
        std::cout << e << '\n';
    }
    std::cout << '\n';
}

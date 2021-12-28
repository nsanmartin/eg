#include <vector>
#include <ranges>
#include <iostream>

int main()
{
    std::vector<int> const vi{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // using namespace ranges;
    auto filter_fun = [](int i){ return i % 2 == 1; };
    auto square = [](int i) { return i * i; };
    auto rng = vi
        | std::views::filter(filter_fun)
        | std::views::transform(square);
    // auto odd = [](int i){ return i % 2 == 1; };
    // auto to_string = [](int i){ return std::to_string(i); };
    // //auto square = [](int i) { return i * i; };
    for (auto e: rng) {
        std::cout << e << '\n';
    }
        

    // for (auto e: vi
    //          | std::views::filter(odd)
    //          | std::views::transform(to_string)) {
    //     std::cout << e << ' ';
    // }
    std::cout << '\n';

// rng == {"2","4","6","8","10"};
    
  // std::vector<int> ints{0,1,2,3,4,5,6};
  // auto even = [](int i){ return 0 == i % 2; };
  // auto square = [](int i) { return i * i; };

  // for (int i : ints | std::views::filter(even) | std::views::transform(square)) {
  //   std::cout << i << ' ';
  // }
}

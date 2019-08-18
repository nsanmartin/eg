#include <iostream>
#include <tuple>
#include <vector>
#include <string>

template<typename ...Ts>
class dataframe {
    std::tuple<std::vector<Ts>...> vectors;
    char mSeparatorChar{' '};
    
public:
    dataframe() : vectors{std::vector<Ts>{}...} {
        static_assert(sizeof...(Ts) > 0); // error: dataframe must have at least one column!
    }


    template<std::size_t... I> 
    auto elements_impl(int index, std::index_sequence<I...>) {
        return std::make_tuple(std::get<I>(vectors).at(index)...);
    }
    auto elements(int index) {
        return elements_impl(index, std::index_sequence_for<Ts...>{});
    }


    
    template<std::size_t... I> 
    void print_impl(int index, std::index_sequence<I...>) {
        (void(std::cout << std::get<I>(vectors).at(index) << mSeparatorChar),...);
    }
    void print(int index) {
        print_impl(index, std::index_sequence_for<Ts...>{});
        std::cout << '\n';
    }

    void print_table() {
        auto n = nrows();
        for (auto i = 0; i < n; ++i) { print(i); }
    }

    template<std::size_t... I> 
    void push_row_impl(std::tuple<Ts...> t, std::index_sequence<I...>) {
        (void(std::get<I>(vectors).push_back(std::get<I>(t))),...);
    }
    
    void push_row(std::tuple<Ts...> t) {
        push_row_impl(t, std::index_sequence_for<Ts...>{});
    }


    auto nrows() const { return std::get<0>(vectors).size(); }

};

int main() {
    dataframe<int, float, std::string, int> df;
    df.push_row(std::make_tuple(23, 98.55f, "fasad", 13));
    df.push_row(std::make_tuple(23, 98.55f, "f__sdfd", 113));
    df.push_row(std::make_tuple(23, 8.0055f, "34t3g%fasad", 1003));

    std::cout << df.nrows() << " rows:\n";
    df.print_table();
}

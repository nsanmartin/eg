// from so
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>

template <size_t index, class Op, class... Ts>
constexpr auto tuple_fold(Op op, const std::tuple<Ts...>& t) {
    if constexpr(index == sizeof...(Ts) - 1) {
        return std::get<index>(t);
    } else {
        return op(std::get<index>(t), tuple_fold<1 + index>(op, t));
    }
}

template <typename ... Ts>
constexpr auto sumT (std::tuple<Ts...> const & t1)  {
  return tuple_fold<0>(std::plus<>{}, t1);
}

int main () {
  std::tuple<int,double> t = {1, 2.0};
  auto s = sumT(t);
  static_assert(std::is_same_v<decltype(s), double>);
  std::cout << s << std::endl;
}

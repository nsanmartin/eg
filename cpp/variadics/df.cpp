#include <iostream>
#include <vector>

// helpers
template <typename T> struct id { using type = T; };

template <typename T> using type_of = typename T::type;

template <size_t... N> struct sizes : id <sizes <N...> > { };

// choose N-th element in list <T...>
template <size_t N, typename... T> struct Choose;

template <size_t N, typename H, typename... T>
struct Choose <N, H, T...> : Choose <N-1, T...> { };

template <typename H, typename... T>
struct Choose <0, H, T...> : id <H> { };

template <size_t N, typename... T>
using choose = type_of <Choose <N, T...> >;

// given L>=0, generate sequence <0, ..., L-1>
template <size_t L, size_t I = 0, typename S = sizes <> > struct Range;

template <size_t L, size_t I, size_t... N>
struct Range <L, I, sizes <N...> > : Range <L, I+1, sizes <N..., I> > { };

template <size_t L, size_t... N>
struct Range <L, L, sizes <N...> > : sizes <N...> { };

template <size_t L>
using range = type_of <Range <L> >;

// single tuple element
template <size_t N, typename T>
class TupleElem {
    std::vector<T> mCol;
public:
    TupleElem() : mCol{std::vector<T>{}} {}
	std::vector<T>&  get() { return mCol; }
	const std::vector<T>& get() const { return mCol; }
};

// tuple implementation
template <typename N, typename... T> class TupleImpl;

template <size_t... N, typename... T>
class TupleImpl <sizes <N...>, T...> : TupleElem <N, T>... {

	template <size_t M> using pick = choose <M, std::vector<T>...>;
	template <size_t M> using col = TupleElem <M, pick <M> >;

public:
	template <size_t M>
	pick <M>& get() { return col <M>::get(); }

	template <size_t M>
	const pick <M>& get() const { return col <M>::get(); }
};

template <typename... T>
struct Tuple : TupleImpl <range <sizeof...(T)>, T...>
{
    static constexpr std::size_t size() { return sizeof...(T); }
};

int main()
{
    using namespace std;
    TupleElem<0,int> t_int;
    Tuple<int, int> t_int_int;
    // Tuple<int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int> test;
    // Tuple<> test2;

    t_int.get().push_back(17);
    std::cout << "pushed: " << t_int.get().back() << '\n';
    //t_int.get<0>().push_back(1);
    // test.get<1>() = 2;

    // cout << test.size() << endl;
    // cout << test.get<0>() << endl;
    // cout << test.get<1>() << endl;
}

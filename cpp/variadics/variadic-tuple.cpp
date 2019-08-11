// so: questions/27941661/generating-one-class-member-per-variadic-template-argument
#include <iostream>
#include <vector>
#include <tuple>
#include <functional>

template<class T1, class T2> struct AreSameType { static const bool value = false; };
template<class T> struct AreSameType<T,T> { static const bool value = true; };


template<typename... Types>
class dataframe {
public:
    typedef std::tuple<std::vector<Types>...> vtype;
    vtype vectors;

    template<int N, typename T>
    struct VectorOfType:
	AreSameType<T,typename std::tuple_element<N, vtype>::type::value_type>
    {};

    template<int N, class T, class Tuple, bool Match = false>
    struct MatchingField {
	static std::vector<T>& get(Tuple& tp) {
	    return MatchingField<N+1, T, Tuple, VectorOfType<N+1, T>::value>::get(tp);
	}
    };


    template<int N, class T, class Tuple>
    struct MatchingField<N, T, Tuple, true> {
	static std::vector<T>& get(Tuple& tp) { return std::get<N>(tp); }
    };
    
    template<typename T>
    std::vector<T>& access() {
	return MatchingField<0, T, vtype, VectorOfType<0, T>::value>::get(vectors);
    }
};
				  

int main () {
    int twelf = 12.5;
    typedef std::reference_wrapper<int> rint;

    dataframe<float, rint> mc;
    
    std::vector<rint>& i = mc.access<rint>();

    i.push_back(twelf);

    mc.access<float>().push_back(10.5);

    std::cout << "floats: " << mc.access<float>()[0] << '\n'
    	      << "ints: " << mc.access<rint>()[0] << '\n';


    dataframe<int, std::string, std::string, int, float> df;
    auto x = df.access<int>();
}

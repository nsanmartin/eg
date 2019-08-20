#include <iostream>
#include <tuple>
#include <vector>
#include <cassert>
#include <fstream>
#include <sstream>
#include <numeric>

template<typename... Ts, std::size_t... I>
void get_sizes_impl(std::tuple<std::vector<Ts>...>& t, std::vector<std::size_t>& szs, std::index_sequence<I...>) {
    ((szs.push_back(std::get<I>(t).size())), ...);
}

template<typename... Ts>
void get_sizes(std::tuple<Ts...>& t, std::vector<std::size_t>& szs) {
    return get_sizes_impl(t, szs, std::index_sequence_for<Ts...>{});
}

template<typename... Ts>
class dataframe {
    using names_t = std::array<std::string, sizeof...(Ts)>;
    
    std::tuple<std::vector<Ts>...> mVectors;
    char mSeparatorChar;

    template<std::size_t... I>
    void push_back_impl(std::tuple<Ts...> row, std::index_sequence<I...>) {
	(void(std::get<I>(mVectors).push_back(std::get<I>(row))),...);
    }

    template<std::size_t... I>
    auto make_tuple_impl(std::vector<std::string> string_vector, std::index_sequence<I...>) const {
    	return std::make_tuple(parse_item<Ts>(string_vector.at(I))...);
    }

    template <typename T>
    T parse_item(const std::string& item) const {
	T x;
	std::stringstream ss{item};
	ss >> x;
	return x;
    }

    template<std::size_t... I>
    std::ostream& out_stream_row_impl(std::ostream& os, int index, std::index_sequence<I...>) const {
	(void(os << std::get<I>(mVectors).at(index) << mSeparatorChar ),...);
	return os;
    }

public:
    dataframe(char sep = ' ', names_t names = names_t{})
	: mVectors{std::vector<Ts>{}...}, mSeparatorChar{sep}, mNames{names} {
	static_assert(sizeof...(Ts) > 0 );
    }

    dataframe(const char* filename, char sep = ' ', names_t names = names_t{})
	: dataframe{sep, names} {
	read_file(std::string{filename});
    }

    dataframe(const std::string& filename, char sep = ' ', names_t names = names_t{})
	: dataframe{filename.c_str(), sep, names} {}

    dataframe(std::tuple<std::vector<Ts>...> vectors, char sep = ' ', names_t names = names_t{})
	: mVectors{vectors}, mSeparatorChar{sep}, mNames{names} {
	    static_assert(sizeof...(Ts) > 0 );
	    std::vector<std::size_t> szs;
	    get_sizes(vectors, szs);
	    auto last = szs.back();
	    assert(std::accumulate(szs.begin(), szs.end() - 1, true,
				   [&last](bool all_equal, std::size_t s) { return all_equal && s == last; }));
    }


    
    template<typename T>
    auto cbind(std::vector<T>&& v, std::string nm = "__") {
	std::array<std::string, sizeof...(Ts) + 1> names;

	std::copy(std::begin(mNames), std::end(mNames), std::begin(names));
	names.back() = nm;
    	return dataframe<Ts...,T>{std::tuple_cat(mVectors, std::make_tuple(v)), mSeparatorChar, names};
    }

    auto nrows() const { return std::get<0>(mVectors).size(); }
    static constexpr auto ncols()  { return sizeof...(Ts); }
    std::array<std::string, ncols()> mNames;

    void push_back(std::tuple<Ts...> row) { push_back_impl(row, std::index_sequence_for<Ts...>{}); }
    auto make_tuple(std::vector<std::string> string_vector) const {
	return make_tuple_impl(string_vector, std::index_sequence_for<Ts...>{});
    }
	    
    

    template<std::size_t... I>
    auto at_impl(int index, std::index_sequence<I...>) {
	return std::make_tuple(std::get<I>(mVectors).at(index)...);
    }
    auto at(int index) { return at_impl(index, std::index_sequence_for<Ts...>{}); }

    
    template<std::size_t I>
    auto col() { return std::get<I>(mVectors); }

    template<std::size_t I>
    auto colsum() {
	auto vec = std::get<I>(mVectors);
	typename decltype(vec)::value_type sum{};
	for (auto& x: vec) { sum += x; };
	return sum;
    }


    template<std::size_t... I>
    auto colSums_impl(std::index_sequence<I...>) {
	return std::make_tuple(colsum<I>()...);
    }
    auto colSums() { return colSums_impl(std::index_sequence_for<Ts...>{}); }

    
    template<std::size_t I>
    double mean() {
	auto sum = colsum<I>();
	return static_cast<double>(sum) / static_cast<double>(nrows());
    }

    std::ostream& out_stream_row(std::ostream& os, int index) const {
	out_stream_row_impl(os, index, std::index_sequence_for<Ts...>{});
	return os << '\n';
    }

    void print_names(std::ostream& os) const {

	for (auto& s: mNames) { os << s << mSeparatorChar; }
	os << '\n';
    }

    std::ostream& out_stream(std::ostream& os) const {
	print_names(os);
	auto n = nrows();
	for (auto i = 0; i < n; ++i) { out_stream_row(os, i);}
	return os;
    }
    
    void read_file(const std::string& filename);
    std::vector<std::string> read_line(const std::string& line);

    template<typename T, bool isNumber> struct print_numeric_item {
	void operator()(std::ostream& os, T& item) { os << item << ' '; }
    };

    template<typename T> struct print_numeric_item<T, false> {
	void operator()(std::ostream& os, T& item) { os << "NaN "; }
    };
    
    template <typename... Us, std::size_t... I>
    void print_row_numbers_impl (std::ostream& os, std::tuple<Ts...>& t, std::index_sequence<I...>) {
	((print_numeric_item<Ts,std::is_arithmetic<Ts>::value>{}(os,std::get<I>(t))),...);
    }

};

template<typename... Ts>
void dataframe<Ts...>::read_file(const std::string& filename) {
    if (auto fstream = std::ifstream{filename}) {
	std::string line;
	while (std::getline(fstream, line)) {
	    auto line_vector = read_line(line);
	    auto t = make_tuple(line_vector);
	    push_back(t);
	}
    }
}

template<typename... Ts>
std::vector<std::string> dataframe<Ts...>::read_line(const std::string& line) {
    std::vector<std::string> res;
    auto delim = std::string{mSeparatorChar};
    auto start = 0L;
    auto end = line.find(delim);
    while (end != std::string::npos) {
	auto word = line.substr(start, end - start);
	res.emplace_back(word);
	start = end + delim.length();
	end = line.find(delim, start);
    }
    res.emplace_back(line.substr(start, end - start));
    assert(res.size() == ncols());
    return res;
}

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, const dataframe<Ts...>& df) {
     return df.out_stream(os);
}


class iris : public dataframe<double, double, double, double, std::string> {
public:
    enum { SepalLength = 0, SepalWidth, PetalLength, PetalWidth, Species, NCOLS };
    iris(const std::string& fname, char sep = ' ')
    	: dataframe {fname, sep, {
    	    "SepalLength", "SepalWidth", "PetalLength", "PetalWidth", "Species" }}
    	{
    	    static_assert(ncols() == NCOLS );
    	}
};


class mtcars
    : public dataframe<std::string, double, int, double, int, double, double, double, int, int, int, int> {
public:
    enum { marca = 0, mpg, cyl, disp, hp, drat, wt, qsec, vs, am, gear, carb, NCOLS };
    mtcars(const std::string& fname, char sep = '\t')
	: dataframe{fname, sep,{"marca", "mpg", "cyl", "disp", "hp", "drat", "wt", "qsec", "vs", "am", "gear", "carb"}}
	{
	    static_assert(ncols() == NCOLS );
	}
};

template<typename T, bool isNumber> struct print_numeric_item {
    void operator()(std::ostream& os, T& item) { os << item << ' '; }
};

template<typename T> struct print_numeric_item<T, false> {
    void operator()(std::ostream& os, T& item) { os << "NaN "; }
};

template <typename... Ts, std::size_t... I>
void print_tuple_numbers_impl (std::ostream& os, std::tuple<Ts...>& t, std::index_sequence<I...>) {
    ((print_numeric_item<Ts,std::is_arithmetic<Ts>::value>{}(os,std::get<I>(t))),...);
}

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, std::tuple<Ts...>& t) {
    print_tuple_numbers_impl(os,t, std::index_sequence_for<Ts...>{});
    return os;
}


int main () {
    iris ir{"data/iris.csv"};
    mtcars mtc{"data/mtcars.csv"};
    std::cout << mtc ;
    auto cs_mtc = mtc.colSums();
    auto cs_ir = ir.colSums();
    std::cout << cs_mtc << '\n';
    std::cout << cs_ir <<'\n';

    auto z = mtc.cbind(mtc.col<mtcars::marca>(), "MARCA:)");
    std::cout << z << '\n';

}

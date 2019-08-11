#include <iostream>
#include <vector>
#include <string>
#include <tuple>


template<typename TupleType>
class df {
    TupleType mTuple;
    std::vector<std::string> mNames;
public:
    df(TupleType t, std::vector<std::string> ns) : mTuple{t}, mNames{ns} {}
    
};


int main () {
    df<std::tuple<std::vector<int>, std::vector<bool>, std::vector<std::string>>>
        df_0{std::make_tuple(std::vector<int>{},
                             std::vector<bool>{},
                             std::vector<std::string>{}),
             {"Int", "Bool", "String"}};
}

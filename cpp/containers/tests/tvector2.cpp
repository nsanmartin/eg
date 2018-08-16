#include <iostream>
#include <vector>
#include "../vector.hpp"

#define NL std::cout << std::endl

template<typename T>
void print_vec(vector<T>& v, const char * msg) {
     std::cout << msg 
               << "size: " << v.size() << "\t"
               << "capacity: " << v.max_capacity() << std::endl;
}

int main(int argc, char** argv) {
     // vector<int> v(0);
     // vector<int> w(v);
     // for (int i = 1; i < 32; i++)
     //      v.push_back(i);
     // vector<int> x(v);
     // //for (int* it = v.begin(); it != v.end(); it++)
     // for (auto& x : v)
     //      std::cout << x << " ";
     // NL;

     // print_vec(v, "v: ");
     // print_vec(w, "w: ");
     // print_vec(x, "x: ");
     // while (x.size())
     //      std::cout << "pop: " << x.pop_back() << " ";
     // NL;
     // print_vec(x, "x: ");
     
     // for (auto& x : v)
     //      std::cout << x << " ";

     // NL;
     
     vector<int> z{};
     print_vec(z, "z{}: ");
     for (int i = 1; i < 32; i++)
          z.push_back(i);
     print_vec(z, "z after pushing: ");
     while (z.size())
          std::cout << "pop: " << z.pop_back() << " ";
     NL;
          
          
}

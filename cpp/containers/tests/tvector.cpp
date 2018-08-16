#include <iostream>
#include <vector>
#include "../vector.hpp"

template<typename T>
void print_vec(vector<T>& v, const char * msg) {
     std::cout << msg 
               << "size: " << v.size() << "\t"
               << "capacity: " << v.max_capacity() << std::endl;
}

int main(int argc, char** argv) {
     vector<int> v(0);
     vector<int> w(v);
     for (int i = 1; i < 16; i++)
          v.push_back(i);
     vector<int> x(v);
     //for (int* it = v.begin(); it != v.end(); it++)
     for (auto& x : v)
          std::cout << x << std::endl;

     print_vec(v, "v: ");
     print_vec(w, "w: ");
     print_vec(x, "x: ");
}

#include <iostream>
#include "../list.hpp"

//using namespace std;

int main () {
     list<int> l;
     l.push(1);
     l.push(7);
     for (int i = 0; i < 111; i++)
          l.push(i);
     
     list<int>::Node * n = l.first_node();

     for (int i = 0; i < l.size(); i++) {
          std::cout << n ->value() << " ";
          n = n -> next();
     }
     std::cout << std::endl;

     std::cout << "front: " << l.front() << std::endl;
     std::cout << "back: " << l.back() << std::endl;
     
     int t;
     for (!l.empty(); t = l.pop();) {
          std::cout << t << " ";
     }
     std::cout << std::endl;
     return 0;
}

#include <iostream>
#include "lista.hpp"

using namespace std;

int main () {
     List<int> l;
     l.push(1);
     l.push(7);
     for (int i = 0; i < 111; i++)
          l.push(i);
     
     Node<int> * n = l.first_node();

     for (int i = 0; i < l.size(); i++) {
          cout << n ->value() << " ";
          n = n -> next();
     }
     cout << endl;

     cout << "front: " << l.front() << endl;
     cout << "back: " << l.back() << endl;
     
     int t;
     for (!l.empty(); t = l.pop();) {
          cout << t << " ";
     }
     cout << endl;
     return 0;
}

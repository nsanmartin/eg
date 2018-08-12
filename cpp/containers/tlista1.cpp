#include <iostream>
#include "lista.hpp"

#include <stdio.h>

using namespace std;

int main () {
     List<int> l;
     l.push(1);
     l.push(7);
     for (int i = 0; i < 111; i++)
          l.push(i);
     
     Node<int> * n = l.first_node();
     int c = 0;

     
     for (List<int>::iterator iter = l.begin();
          iter != l.end(); ++iter) {
          cout << *iter << " ";
     }

     cout << endl;

     cout << "front: " << l.front() << endl;
     cout << "back: " << l.back() << endl;
     
     while (!l.empty()) { cout << l.pop() << " "; }
     cout << endl;
     return 0;
}

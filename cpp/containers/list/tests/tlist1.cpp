#include <iostream>
#include "../list.hpp"

#include <stdio.h>

using namespace std;

int main () {
    eg::list<int> l;
    l.push_back(1);
    l.push_back(7);
    for (int i = 0; i < 111; i++)
        l.push_back(i);
     
    eg::list<int>::Node * n = l.first_node();
    int c = 0;

     
    for (eg::list<int>::iterator iter = l.begin();
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

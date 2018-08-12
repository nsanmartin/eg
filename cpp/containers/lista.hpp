#ifndef _LISTA_H
#define _LISTA_H

#include <iostream>

#include "node.hpp"

using namespace std;

template<class T>
class List {
     Node<T> *_first;
     int _size;
     // pre: size > 0
     Node<T> * last_node() { return _first -> prev(); } 
public:
     class iterator {
          Node<T>* n;
          //friend class List;
     public:
          iterator();
          iterator(Node<T>* n) : n(n) {}
          //iterator(const iterator&);
          //~iterator();

          iterator& operator=(const iterator& other) {
               n = other.n;
          }
          bool operator==(const iterator& other) const {
               return n == other.n;
          }
          bool operator!=(const iterator& other) const {
               return n != other.n;
          }

          iterator& operator++() { n = n->next(); return *this; }

          const T& operator*() const { return n -> value(); };
          // pointer operator->() const;

     };

     iterator begin () { return _first; }
     iterator end () { return _first -> prev(); }
     
     List<T>() : _first(NULL), _size(0) {}
     // List<T>(List<T>& l);
     ~List<T>() { while (_size > 0) { pop(); } }
     
     bool empty() const { return !_size; }
     int size() const { return _size; }

     const T& front() const { return _first -> value(); }
     const T& back() const { return _first -> prev() -> value(); }
     
     
     Node<T>* first_node() { return _first; }
     void push(T e);
     T pop();
};

template<class T>
void List<T>::push(T e) 
{
     if (!_first) {
          Node<T>* tmp = new Node<T>(e);
          _first = tmp;
     } else {
          Node<T> * ult = last_node();
          Node<T> * n = new Node<T>(e, ult, _first);
          ult -> set_next(n);
          _first -> set_prev(n);
                    
     }
     _size++;
}


template<class T>
T List<T>::pop() {
     Node<T> * ult = last_node();
     T res(ult -> value());
     ult -> prev() -> set_next(ult -> next()) ;
     ult -> next() -> set_prev(ult -> prev()) ;
     _size--;
     delete ult;
     ult = NULL;
     return res;
}


#endif // _LISTA_H

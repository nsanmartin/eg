#ifndef _LIST_H
#define _LIST_H

#include <iostream>

template<class T>
class list {
public:
    class Node {
        T data;
        Node * _next;
        Node * _prev;
    public:
        Node * next() const { return _next; }
        Node * prev() const { return _prev; }
        void set_next(Node * next) { _next = next; }
        void set_prev(Node * prev) { _prev = prev; }
        const T& value() const { return data; } 

        Node(T e) : data(e), _prev(this), _next(this) {  }
        Node(T e, Node * prev, Node * next)
            :  data(e), _prev(prev), _next(next) { }
        ~Node() { }
    };

    class iterator {

        Node* n;
        //friend class list;
    public:
        iterator();
        iterator(Node* n) : n(n) {}
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
     
    list<T>() : _first(NULL), _size(0) {}
    // list<T>(list<T>& l);
    ~list<T>() { while (_size > 0) { pop(); } }
     
    bool empty() const { return !_size; }
    int size() const { return _size; }

    const T& front() const { return _first -> value(); }
    const T& back() const { return _first -> prev() -> value(); }
     
     
    Node* first_node() { return _first; }
    void push(T e);
    T pop();

private:
    Node *_first;
    int _size;
    // pre: size > 0
    Node * last_node() { return _first -> prev(); } 

};

template<class T>
void list<T>::push(T e) 
{
    if (!_first) {
        Node* tmp = new Node(e);
        _first = tmp;
    } else {
        Node * ult = last_node();
        Node * n = new Node(e, ult, _first);
        ult -> set_next(n);
        _first -> set_prev(n);
                    
    }
    _size++;
}


template<class T>
T list<T>::pop() {
    Node * ult = last_node();
    T res(ult -> value());
    ult -> prev() -> set_next(ult -> next()) ;
    ult -> next() -> set_prev(ult -> prev()) ;
    _size--;
    delete ult;
    ult = NULL;
    return res;
}


#endif // _LIST_H

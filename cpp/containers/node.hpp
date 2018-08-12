#ifndef _NODE_H
#define _NODE_H

template <class T>
class Node {
     T data;
     Node<T> * _next;
     Node<T> * _prev;
public:
     Node<T> * next() const { return _next; }
     Node<T> * prev() const { return _prev; }
     void set_next(Node<T> * next) { _next = next; }
     void set_prev(Node<T> * prev) { _prev = prev; }
     const T& value() const { return data; } 

     Node(T e) : data(e), _prev(this), _next(this) {  }
     Node(T e, Node<T> * prev, Node<T> * next)
          :  data(e), _prev(prev), _next(next) { }
     ~Node() { }
};

#endif /* _NODE_H */

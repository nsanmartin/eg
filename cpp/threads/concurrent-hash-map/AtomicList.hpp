#ifndef _ATOMIC_LIST_H_
#define _ATOMIC_LIST_H_

#include <atomic>

template <typename T>
class Lista {
private:
	struct Node {
		Node(const T& val) : _val(val), _next(nullptr) {}
		T _val;
		Node *_next;
	};

	std::atomic<Node *> _head;

public:
	Lista() : _head(nullptr) {}
	~Lista();

    void push_front(const T& val);

	const T& front() const { return _head.load()->_val; }
	const T& ith(int i) const;

	class iterator {
	public:
        iterator() : _lista(nullptr), _n(nullptr) {}
        iterator(Lista<T>* lista,typename Lista<T>::Node* sig)
            : _lista(lista), _n(sig) {}

		iterator& operator=(const typename Lista::iterator& otro){
                _lista = otro._lista;
                _n = otro._n;
                return *this;
        }


        iterator& operator++() { _n = _n->_next; return *this; }
        
		bool operator==(const typename Lista::iterator& otro)
            const {
			return
                _lista->_head.load() == otro._lista._head.load()
                && _n == otro._n;
		}
        
        bool operator!=(const typename Lista::iterator& otro)
            const {
			return
                _lista->_head.load() != otro._lista->_head.load()
                || _n != otro._n;
		}

        T& operator*() const { return _n -> _val; };
        T* operator->() { return &(_n -> _val); }

	private: // iterator
		Lista *_lista;
		typename Lista::Node *_n;
	};

    iterator begin() { return iterator(this, _head); }
    iterator end() { return iterator(this, nullptr); }
};

template <typename T>
Lista<T>::~Lista() {
		Node *n, *t;
		n = _head.load();
		while (n) {
			t = n;
			n = n->_next;
			delete t;
		}
}

template <typename T>
void Lista<T>::push_front(const T& val) {
    Node * n = new Node(val);
    n -> _next = _head.load();
    //CRIT
    // if fail expected, compare_exchange_weak loads
    // the actual value stored in *this into expected.
    while (!_head.compare_exchange_weak(n -> _next, n));
    //EXIT
}

template<typename T>
const T& Lista<T>::ith(int i) const {
    Node *n = _head.load();
    int j;
    for (int j = 0; j < i; j++)
        n = n->_next;
    return n->_val;
}
     
#endif /* _ATOMIC_LIST_H_ */

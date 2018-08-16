#include <cstring>

template<typename T>
class vector {
    T *elem;
    int sz;
    int capacity;
public:
    vector(int s = 0) {
        if (s < 0)
            throw std::runtime_error(std::string{
                    "negative size for vector"});
        elem = new T[sz=s];
        capacity = sz + 4;
    }

    vector(const vector& v);
    vector& operator=(const vector& v);
     
    ~vector() { delete[] elem; }

    T& operator[](int i);

    T* begin() { return elem; }
    T* end() { return elem + sz; }
    const T* begin() const { return elem; }
    const T* end() const { return elem + sz; }

    int size() const { return sz;};
    int max_capacity() const { return capacity; }
    void push_back(const T&);
    T& pop_back();
};


template<typename T>
vector<T>::vector(const vector& v)
    : elem{new T[v.sz + 4]}, sz{v.sz}, capacity{v.sz + 4}
{
    std::copy(v.begin(), v.end(), elem);
}

template<typename T>
T& vector<T>::operator[](int i) {
    if (i < 0 || sz <= i)
        throw std::runtime_error(std::string{
                "index out of range"});
    return elem[i];
}


template<typename T>
void vector<T>::push_back(const T& x) {
    if (sz == capacity) {
        T* a = new T[capacity+=capacity];
        std::copy(elem, elem + sz, a);
        delete [] elem;
        elem = a;
    }

    elem[sz++] = x;
}


template<typename T>
T& vector<T>::pop_back() {
    if (!sz)
        throw std::runtime_error(std::string{
                "negative size for vector"});
    if (sz < capacity/4) {
        T* a = new T[capacity /= 2];
        std::copy(elem, elem + sz, a);
        delete [] elem;
        elem = a;
    }
    return elem[--sz];
}

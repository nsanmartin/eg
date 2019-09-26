#include <cstring>
#include <memory>

namespace eg {
    
    template<typename T>
    class vector {
    public:
        using iterator = T*;
    private:
        std::unique_ptr<T[]> elem;
        int sz;
        int capacity;
    public:

        
        vector(int s = 0) : sz{s} {
            if (s < 0)
                throw std::runtime_error(std::string{"negative size for vector"});
            
            capacity = sz + 4;
            elem.reset(new T[capacity]);
        }

        vector(const vector& v);
        vector& operator=(const vector& v);
     
        // ~vector() { delete[] elem; }

        T& operator[](int i);

        T* begin() { return elem.get(); }
        T* end() { return elem.get() + sz; }
        const T* begin() const { return elem.get(); }
        const T* end() const { return elem.get() + sz; }

        int size() const { return sz;};
        bool empty() const { return size() == 0; }
        int max_capacity() const { return capacity; }
        void push_back(const T&);
        void pop_back();
        T& back() { return elem[sz-1];}
    };


    template<typename T>
    vector<T>::vector(const vector& v)
        : elem{new T[v.capacity]}, sz{v.sz}, capacity{v.capacity}
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
            std::unique_ptr<T[]> a {new T[capacity+=capacity]};
            std::copy(begin(), end(), a.get());
            elem.swap(a);
        }

        elem[sz++] = x;
    }


    template<typename T>
    void vector<T>::pop_back() {
        if (!sz)
            throw std::runtime_error(std::string{"negative size for vector"});
        if (sz < capacity/4) {
            std::unique_ptr<T[]> a {new T[capacity /= 2] };
            std::copy(begin(), end(), a.get());
            elem.swap(a);
        }
        --sz;
        return;
    }
}

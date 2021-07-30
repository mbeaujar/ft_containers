#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <iostream>
#include <memory>

namespace ft
{
    template <typename T>
    class Myiterator
    {
    private:
        T *ptr;

    public:
        Myiterator() : ptr(nullptr){};
        Myiterator(T *p) : ptr(p){};
        ~Myiterator(){};

        T operator*() const
        {
            return *ptr;
        }

        bool operator!=(Myiterator const &right) {
            return this->ptr != right.ptr;
        }

        Myiterator &operator++()
        {
            ++ptr;
            return *this;
        };

        Myiterator operator++(int)
        {
            Myiterator tmp(*this);
            ++*this;
            return tmp;
        };

        Myiterator &operator--()
        {
            --ptr;
            return *this;
        };

        Myiterator operator--(int)
        {
            Myiterator tmp(*this);
            --*this;
            return tmp;
        };
    };

    template <typename T, class Alloc = std::allocator<T> >
    class vector {
        public:
            typedef T value_type;
            typedef size_t size_type;
            typedef Alloc allocator_type;
            typedef ptrdiff_t difference_type;
            typedef Myiterator<value_type> iterator;

            vector() {
                _arr = _alloc.allocate(1);
                _capacity = 1;
                _current = 0;
            }

            vector(size_type N) { // make exceptions for the case where N is under 0
                _arr = _alloc.allocate(N);
                _capacity = N;
                _current = N;
            };

            vector(size_type N, value_type val) {
                _arr = _alloc.allocate(N);
                _capacity = N;
                _current = N;
                for (size_type i = 0; i < N; i++)
                    _arr[i] = val;
            }

            ~vector() {
               _alloc.deallocate(_arr, _capacity);
            };

            T& operator[](size_type idx) {
                return _arr[idx];
            };

            void push_back(T content) {
                if (_current == _capacity) {
                    T *old = _arr;
                    _arr = _alloc.allocate(_capacity = _capacity * 2);
                    for (size_type i = 0; i < _current; i++)
                        _arr[i] = old[i];
                    delete [] old;
                }
                this->_arr[this->_current++] = content;
            };


            size_type size() const {
                return _current;
            };

            iterator begin() const {
                return iterator(_arr);
            };

            iterator end() const {
                return iterator(_arr + _current);
            };

        private:
            allocator_type _alloc;
            T *_arr;
            size_type _capacity;
            size_type _current;
    };
};

#endif
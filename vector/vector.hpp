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

            vector(size_type N = 0) { // make exceptions for the case where N is under 0
                this->arr = new T[N];
                this->capacity = N;
                this->current = N;
            };


            ~vector() {
                delete [] this->arr;
            };

            T& operator[](size_type idx) {
                return this->arr[idx];
            };

            void push_back(T content) {
                if (this->current == this->capacity) {
                    T *old = this->arr;
                    this->arr = new T[this->capacity = this->capacity * 2];
                    for (size_type i = 0; i < this->current; i++)
                        this->arr[i] = old[i];
                    delete [] old;
                }
                this->arr[this->current++] = content;
            };


            size_type size() const {
                return this->current;
            };

            iterator begin() const {
                return iterator(this->arr);
            };

            iterator end() const {
                return iterator(this->arr + this->current);
            };

        private:
            T *arr;
            size_type capacity;
            size_type current;
    };
};

#endif
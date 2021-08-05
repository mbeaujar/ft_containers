#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include "iterator.hpp"
#include "utils.hpp"
#include <iostream>
#include <memory>

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T 																value_type;
		typedef Alloc															allocator_type;
		typedef typename allocator_type::reference								reference;
		typedef typename allocator_type::const_reference						const_reference;
		typedef typename allocator_type::pointer								pointer;
		typedef typename allocator_type::const_pointer							const_pointer;
		typedef ft::random_access_iterator<value_type>							iterator;
		typedef ft::random_access_iterator<const value_type>					const_iterator;
		typedef	ft::reverse_iterator<iterator>									reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type			difference_type;
		typedef typename allocator_type::size_type								size_type;

	private:
		allocator_type _alloc;
		pointer _arr;
		size_type _capacity;
		size_type _current;

	public:
		//// ----------------------------------- Member Functions

		explicit vector(const allocator_type &alloc = allocator_type())
		:
			_alloc(alloc),
			_arr(_alloc.allocate(1)),
			_capacity(1),
			_current(0)
		{}

		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		:
			_alloc(alloc),
			_arr(_alloc.allocate(n)),
			_capacity(n),
			_current(n)
		{
			for (pointer it = _arr; n; n--, it++)
				_alloc.construct(it, val);
		}
        
	
		template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
        :
            _alloc(alloc)
		{
			size_type n = 0;
			for (InputIterator tmp = first; tmp != last; tmp++)
				n++;
			_arr = _alloc.allocate(n);
			_capacity = n;
			_current = n;
			for (pointer it = _arr; first != last; first++, it++)
				_alloc.construct(it, *first);
		}

		vector (const vector& x)
		:
			_alloc(x._alloc)
		{
			pointer first = x.begin();
			pointer last = x.end();
			size_type n = 0;
			for (pointer tmp = first; tmp != last; tmp++)
				n++;
			_arr = _alloc.allocate(n);
			_capacity = n;
			_current = n;
			for (pointer it = _arr; first != last; first++, it++)
				_alloc.construct(it, *first);

		}
		
		~vector() {
			_alloc.deallocate(_arr, _capacity);
		}

		vector& operator= (const vector& x) {
			if (this == &x)
				return *this;
			pointer first = x.begin();
			pointer last = x.end();
			size_type n = 0;
			for (pointer tmp = first; tmp != last; tmp++)
				n++;
			_alloc.deallocate(_arr, _capacity);
			_arr = _alloc.allocate(n);
			_capacity = n;
			_current = n;
			for (pointer it = _arr; first != last; first++, it++)
				_alloc.construct(it, *first);
			return *this;
		}


		//// --------------------------------------------- Iterators 

		iterator begin() {
			return iterator(_arr);
		} 

 		const_iterator begin() const {
			return const_iterator(_arr);
		} 

		iterator end() {
			if (this->empty())
				return this->begin();
			return iterator(_arr + _current);
		}

		const_iterator end() const {
			if (this->empty())
				return this->begin();
			return const_iterator(_arr + _current);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(_arr + _current);
		}
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(_arr + _current);
		}

		reverse_iterator rend() {
			return reverse_iterator(_arr);
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(_arr);
		}


		// ----------------------------------- Capacity

		size_type size() const {
			return _current;
		}

		size_type max_size() const {
			return allocator_type().max_size();
		}

		void resize (size_type n, value_type val = value_type()) {
			size_type l = _current;

			if (n < _current) {
				_current = n;
				return;
			}
			if (n > _capacity) {
				pointer New = _alloc.allocate(n);
				for (l = 0; l < _current; l++)
					New[l] = _arr[l];
				_alloc.deallocate(_arr, _capacity);
				_capacity = n;
				_arr = New;
			}
			for (; l < n; l++)
				_arr[l] = val;
			_current = n;
		}

		size_type capacity() const {
			return _capacity;
		}

		bool empty() const {
			return _current == 0;
		}

		void reserve (size_type n) {
			if (n > max_size())
				throw std::length_error("size_type n is greater than max_size");
			if (n < _capacity)
				return;
			pointer tmp = _alloc.allocate(n);
			for (size_type l = 0; l < _current; l++)
				tmp[l] = _arr[l];
			_alloc.deallocate(_arr, _capacity);
			_arr = tmp;
			_capacity = n;
		}

		// ----------------------------- Element access

		reference operator[] (size_type n) {
			return _arr[n];
		}

		const_reference operator[] (size_type n) const {
			return _arr[n];
		}
 
		reference at (size_type n) {
			if (n < 0 || n > _current)
				throw std::out_of_range("n out of range");
			return _arr[n];
		}

		const_reference at (size_type n) const {
			if (n < 0 || n > _current)
				throw std::out_of_range("n out of range");
			return _arr[n];
		}

      	reference front() {
			return *_arr;
		}

		const_reference front() const {
			return *_arr;
		}

		reference back() {
			return *(_arr + _current - 1);
		}

		const_reference back() const {
			return *(_arr + _current - 1);
		}
 
		// -------------------------- Modifiers

		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last) {
			size_type n = 0;

			for (InputIterator tmp = first; tmp != last; tmp++)
				n++;
			if (n > _capacity) {
				_alloc.deallocate(_arr, _capacity);
				_arr = _alloc.allocate(n);
				_capacity = n;
			}
			_current = n;
			for (pointer it = _arr; first != last; first++, it++)
				_alloc.construct(it, *first);
		}

		void assign (size_type n, const value_type& val) {
			if (n > _capacity) {
				_alloc.deallocate(_arr, _capacity);
				_arr = _alloc.allocate(n);
				_capacity = n;
			}
			_current = n;
			for (pointer it = _arr; n; n--, it++)
				_alloc.construct(it, val);
		}

		void push_back (const value_type& val) {
			if (_current == _capacity) {
				pointer tmp = _arr;
				size_type old_capacity = _capacity;
				_arr = _alloc.allocate(_capacity = _capacity * 2);
				for (size_type n = 0; n < _current; n++)
					_arr[n] = tmp[n];
				_alloc.deallocate(tmp, old_capacity);
			}
			_arr[_current] = val;
			_current++;
		}

		void pop_back() {
			_alloc.destroy(_arr + --_current);
		}

		allocator_type get_allocator() const {
			return _alloc;
		};
 
		iterator insert (iterator position, const value_type& val) {
 			if (_current + 1 == _capacity) {
				pointer tmp = _arr;
				size_type old_capacity = _capacity;
				_arr = _alloc.allocate(_capacity = _capacity * 2);
				for (size_type n = 0; n < _current; n++)
					_arr[n] = tmp[n];
				_alloc.deallocate(tmp, old_capacity);
			}
			_current++;
			value_type tmp = *position;
			*position = val;
			iterator it = position;
			++it;
			for (size_type l = (&(*position) - _arr); l < _current; l++, it++) {
				value_type stock = tmp;
				tmp = *it;
				*it = stock;
			} 
			return position;
		}

		//void insert (iterator position, size_type n, const value_type& val); 

		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last);
	};
};

#endif
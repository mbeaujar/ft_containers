#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include "iterator.hpp"
#include "utils.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector {
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
		allocator_type	_alloc;
		pointer 		_arr;
		size_type 		_capacity;
		size_type 		_current;


		// solution -> https://stackoverflow.com/questions/10510077/size-t-convert-cast-to-string-in-c
		template <typename tostring>
		std::string to_string(tostring n) const
		{
			std::ostringstream ss;
			ss << n;
			return ss.str();
		}

	public:
		//// ----------------------------------- Member Functions

		explicit vector(const allocator_type &alloc = allocator_type())
			: _alloc(alloc),
			  //_arr(_alloc.allocate(0)),
			  _arr(0),
			  _capacity(0),
			  _current(0)
		{}

		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			: _alloc(alloc),
			  _arr(_alloc.allocate(n)),
			  _capacity(n),
			  _current(n)
		{
			for (pointer it = _arr; n; n--, it++)
				_alloc.construct(it, val);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
			: _alloc(alloc)
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

		vector(const vector &x)
			: _alloc(x._alloc)
		{
			typename ft::vector<T>::const_iterator first = x.begin();
			typename ft::vector<T>::const_iterator last = x.end();
			typename ft::vector<T>::const_iterator tmp = first;
			size_type n = 0;
			for (tmp = first; tmp != last; tmp++)
				n++;
			_arr = _alloc.allocate(n);
			_capacity = n;
			_current = n;
			for (pointer it = _arr; first != last; first++, it++)
				_alloc.construct(it, *first);
		}

		~vector() {
			this->clear();
			_alloc.deallocate(_arr, _capacity);
		}

		vector& operator= (const vector& x) {
			if (this == &x)
				return *this;
			typename ft::vector<T>::const_iterator first = x.begin();
			typename ft::vector<T>::const_iterator last = x.end();
			typename ft::vector<T>::const_iterator tmp;
			size_type n = 0;
			for (tmp = first; tmp != last; tmp++)
				n++;
			this->clear();
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

			if (n > max_size())
				throw std::length_error("vector::_M_fill_insert");
			if (n < _current) {
				for (; _current > n; _current--)
					_alloc.destroy(_arr + _current);
				return;
			}
			if (n > _capacity) {
				pointer tmp = _alloc.allocate(n);
				for (l = 0; l < _current; l++)
					_alloc.construct(tmp + l, _arr[l]);
				this->clear();
				_alloc.deallocate(_arr, _capacity);
				_current = l;
				_capacity = n;
				_arr = tmp;
			}
			for (; l < n; l++)
				_alloc.construct(_arr + l, val);
			_current = n;
		}

		size_type capacity() const {
			return _capacity;
		}

		bool empty() const {
			return _current == 0;
		}

		void reserve (size_type n) {
			if (n > max_size() || n < 0)
				throw std::length_error("vector::reserve");
			if (n < _capacity)
				return;
			pointer tmp = _alloc.allocate(n);
			size_type l = 0;
			for (; l < _current; l++)
				_alloc.construct(tmp + l, _arr[l]);
			this->clear();
			_alloc.deallocate(_arr, _capacity);
			_arr = tmp;
			_capacity = n;
			_current = l;
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
				throw std::out_of_range("vector::_M_range_check: __n (which is " + to_string(n) + ") >= this->size() (which is " + to_string(this->size()) + ")");
			return _arr[n];
		}

		const_reference at (size_type n) const {
			if (n < 0 || n > _current)
				throw std::out_of_range("vector::_M_range_check: __n (which is " + to_string(n) + ") >= this->size() (which is " + to_string(this->size()) + ")");
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
  		void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
			size_type n = 0;

			for (InputIterator tmp = first; tmp != last; tmp++)
				n++;
			if (n > max_size())
				throw std::bad_alloc();
			if (n > _capacity) {
				this->clear();
				_alloc.deallocate(_arr, _capacity);
				_arr = _alloc.allocate(n);
				_capacity = n;
			}
			else
				this->clear();
			_current = n;
			for (pointer it = _arr; first != last; first++, it++)
				_alloc.construct(it, *first);
		}

		void assign (size_type n, const value_type& val) {
			if (n > max_size() || n < 0)
				throw std::bad_alloc();
			if (n > _capacity) {
				this->clear();
				_alloc.deallocate(_arr, _capacity);
				_arr = _alloc.allocate(n);
				_capacity = n;
			}
			else
				this->clear();
			_current = n;
			for (size_type l = 0; n; n--, l++)
				_alloc.construct(_arr + l, val);
		}

		void push_back (const value_type& val) {
			if (_current == _capacity) {
				pointer tmp = _alloc.allocate(_capacity == 0 ? 1 : _capacity * 2);
				size_type n = 0;
				for (; n < _current; n++)
					_alloc.construct(tmp + n, _arr[n]);
				this->clear();
				_alloc.deallocate(_arr, _capacity);
				_arr = tmp;
				_capacity = _capacity == 0 ? 1 : _capacity * 2;
				_current = n;
			}
			_arr[_current] = val;
			_current++;
		}

		void pop_back() {
			if (_current > 0)
				_alloc.destroy(_arr + --_current);
		}
 
		iterator insert (iterator position, const value_type& val) {
 			size_type pos = (&(*position) - _arr);
			if (_current == _capacity) {
				pointer tmp = _alloc.allocate(_capacity == 0 ? 1 : _capacity * 2);
				size_type l = 0;
				for (; l < pos; l++)
					_alloc.construct(tmp + l, _arr[l]);
				_alloc.construct(tmp + l, val);
				for (;  _capacity != 0 &&  l < _current; l++)
					_alloc.construct(tmp + l + 1, _arr[l]);
				this->clear();
				_alloc.deallocate(_arr, _capacity);
				_arr = tmp;
				_capacity = _capacity == 0 ? 1 : _capacity * 2;
				_current = l + 1;
			}
			else {
				pointer tmp = _alloc.allocate(_current - pos);
				for (size_type i = 0; i < (_current - pos); i++)
					_alloc.construct(tmp + i, *(_arr + pos + i));
				for (size_type l = pos; l < _current; l++)
					_alloc.destroy(_arr + l);
				_alloc.construct(_arr + pos, val);
				size_type i = 0;
				for (size_type l = pos + 1; l < _current + 1; l++, i++) {
					_alloc.construct(_arr + l, *(tmp + i));
					_alloc.destroy(tmp + i);
				}
				_alloc.deallocate(tmp, _current - pos);
				_current++;
			}
			return iterator(_arr + pos);
		}

		void insert (iterator position, size_type n, const value_type& val) {
			size_type pos = (&(*position) - _arr);
			if (n > max_size())
				throw std::length_error("vector:: M fill insert");
 			if (_current + n >= _capacity) {
				pointer tmp = _alloc.allocate(_capacity == 0 ? n : _capacity + n * 2);
				size_type l = 0;
				for (; l < pos; l++)
					_alloc.construct(tmp + l, _arr[l]);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(tmp + l + i, val);
				for (; _capacity != 0 && l < _current; l++)
					_alloc.construct(tmp + l + n, _arr[l]);
				this->clear();
				_alloc.deallocate(_arr, _capacity);
				_arr = tmp;
				_capacity = _capacity == 0 ? n : _capacity + n * 2;
				_current = l + n;
			}
			else {
				for (size_type l = 0; l < n; l++, position++)
					position = this->insert(position, val);
			}
		}

 		template <class InputIterator>
	  	void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
			size_type pos = (&(*position) - _arr);
			size_type n = 0;
			for (InputIterator tmp = first; tmp != last; tmp++)
				n++;
			if (_current + n >= _capacity) {
				pointer tmp = _alloc.allocate(_capacity == 0 ? n : _capacity + n * 2);
				size_type l = 0;
				for (; l < pos; l++)
					_alloc.construct(tmp + l, _arr[l]);
				for (size_type i = 0; i < n && first != last; i++, first++)
					_alloc.construct(tmp + l + i, *first);
				for (; _capacity != 0 && l < _current; l++)
					_alloc.construct(tmp + l + n, _arr[l]);
				this->clear();
				_alloc.deallocate(_arr, _capacity);
				_arr = tmp;
				_capacity = _capacity == 0 ? n : _capacity * 2;
				_current = l + n;
			} else {
				for (size_type l = 0; l < n && first != last; l++, position++, first++)
					position = this->insert(position, *first);
			}
		}

		iterator erase (iterator position) {
			size_type pos = (&(*position) - _arr);
			if (_current > 0) {
				_alloc.destroy(&(*position));
				for (size_type l = pos; l < _current - 1; l++) {
					_alloc.construct(_arr + l, *(_arr + l + 1));
					_alloc.destroy(_arr + l + 1);
				}
				_current--;
			}
			return iterator(_arr + pos);
		}

		iterator erase (iterator first, iterator last) {
			size_type pos = (&(*first) - _arr);
			size_type n = 0;
			for (iterator tmp = first; first != last; first++)
				n++;
			if (_current > 0 && n > 0) {
				for (size_type i = 0; i < n; i++)
					_alloc.destroy(_arr + pos + i);
				for (size_type l = pos; l + n < _current; l++) {
					_alloc.construct(_arr + l, *(_arr + l + n));
					_alloc.destroy(_arr + l + n);
				}
				_current -= n;
			}
			return iterator(_arr + pos);
		}

		void swap (vector& x) {
			if (this == &x)
				return;
			allocator_type tmp_alloc 	= x._alloc;
			pointer tmp_arr 			= x._arr;
			size_type tmp_capacity 		= x._capacity;
			size_type tmp_current 		= x._current;
			x._alloc 					= this->_alloc;
			x._arr 						= this->_arr;
			x._capacity 				= this->_capacity;
			x._current 					= this->_current;
			this->_alloc 				= tmp_alloc;
			this->_arr 					= tmp_arr;
			this->_capacity 			= tmp_capacity;
			this->_current 				= tmp_current;
		}

		void clear() {
			for (; _current > 0; _current--) {
				_alloc.destroy(_arr + _current);
			}
		}

		// ------------------ Allocator

		allocator_type get_allocator() const {
			return allocator_type();
		}
	};

	// ----------------------- Non-member function overloads


	// ------------- relational operators

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename ft::vector<T, Alloc>::const_iterator it = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator first = rhs.begin();

		for (; first != rhs.end() && it != lhs.end(); first++, it++) {
			if (*first != *it)
				return false;
		}
		if (first != rhs.end() || it != lhs.end())
			return false;  
		return true;
	};

	template <class T, class Alloc>
  	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		  return !(lhs == rhs);
	};

	template <class T, class Alloc>
  	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		typename ft::vector<T, Alloc>::const_iterator it = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator first = rhs.begin();

		for (; first != rhs.end() && it != lhs.end(); it++, first++) {
			if (*it < *first)
				return true;
			if (*it > *first)
				return false;
		}
		if (it == lhs.end() && first != rhs.end())
			return true;
		return false;
	};

	template <class T, class Alloc>
  	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		  return (lhs < rhs || lhs == rhs);
	};

	template <class T, class Alloc>
  	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs < rhs) && lhs != rhs; 
	};

	template <class T, class Alloc>
  	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (lhs > rhs || lhs == rhs);
	};

	// ------------------------ Swap 

	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}

};

#endif

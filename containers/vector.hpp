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
		typedef random_access_iterator<value_type>								iterator;
		typedef random_access_iterator<const value_type>						const_iterator;
		//typedef																reverse_iterator;
		//typedef 																const_reverse_iterator;
		typedef typename random_access_iterator<value_type>::difference_type	difference_type;
		typedef typename allocator_type::size_type								size_type;

	private:
		allocator_type _alloc;
		pointer _arr;
		size_type _capacity;
		size_type _current;

	public:
		// ----------------------------------- Constructor
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
                for (pointer it = _arr; first != last ; first++, it++)
                    _alloc.construct(it, *first);
            }   

		// ---------------------------------- Destructor

		~vector() {
			_alloc.deallocate(_arr, _capacity);
		}

		T &operator[](size_type idx) {
			return _arr[idx];
		}

		// ------------------------------------- Methods

		void push_back(T content)
		{
			if (_current == _capacity)
			{
				T *old = _arr;
				_arr = _alloc.allocate(_capacity = _capacity * 2);
				for (size_type i = 0; i < _current; i++)
					_arr[i] = old[i];
				delete[] old;
			}
			_arr[_current++] = content;
		}

		size_type size() const {
			return _current;
		}

		iterator begin() const {
			return iterator(_arr);
		}

		iterator end() const {
			return iterator(_arr + _current);
		}
	};
};

#endif
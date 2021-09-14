#ifndef __BIDIRECTIONAL_ITERATOR_HPP__
#define __BIDIRECTIONAL_ITERATOR_HPP__

#include "binary_search_trees.hpp"

namespace ft 
{
	struct bidirectional_iterator_tag {};

	template <typename T, bool isConst, class Compare = ft::less<T> >
	class bidirectional_iterator : private ft::iterator<bidirectional_iterator_tag, T> {
		public:
			typedef typename ft::enable_if_const<isConst, T>::value_type	value_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::pointer			pointer;
			typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::difference_type	difference_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
		
			bidirectional_iterator()
				: _ptr(0)
			{}

		
			bidirectional_iterator(T* p)
				: _ptr(p)
			{}

			// for const_reverse_iterator, the dumbest thing i have done
			template <typename A, bool B, class C>
			bidirectional_iterator(bidirectional_iterator<A, B, C> const &copy, typename ft::enable_if<!B>::type* = 0)
				: _ptr(copy.base())
			{}

			~bidirectional_iterator() {}

			bidirectional_iterator& operator=(bidirectional_iterator const &copy) {
				if (this == &copy)
					return *this;
				_ptr = copy._ptr;
				return *this;
			}

			T* base() const { return _ptr; }

			//bidirectional_iterator

			bool operator==(bidirectional_iterator const &rhs) { return &_ptr->data.first == &rhs._ptr->data.first; }

			bool operator!=(bidirectional_iterator const &rhs) { return &_ptr->data.first != &rhs._ptr->data.first; }

			value_type& operator*() const { return _ptr->data; }

			pointer operator->() const { return &(operator*()); }

			bidirectional_iterator& operator++() {
				if (_ptr->right) {
					_ptr = _ptr->right;
					while (_ptr->left)
						_ptr = _ptr->left;
				} else {
					while  (_ptr->parent && _ptr->parent->right == _ptr)
						_ptr = _ptr->parent;
					if (_ptr->parent)
						_ptr = _ptr->parent;
				}
				return *this;
			}

			bidirectional_iterator operator++(int) {
				bidirectional_iterator tmp(*this);
				operator++();
				return tmp;
			}

			bidirectional_iterator& operator--() {
				if (_ptr->left) {
					_ptr = _ptr->left;
					while (_ptr->right)
						_ptr = _ptr->right;
				}  else {
					while  (_ptr->parent && _ptr->parent->left == _ptr)
						_ptr = _ptr->parent;
					if (_ptr->parent)
						_ptr = _ptr->parent;
				}
				return *this;
			}

			bidirectional_iterator operator--(int) {
				bidirectional_iterator tmp(*this);
				operator--();
				return tmp;
			}

			operator bidirectional_iterator<const T, true, Compare>() { return bidirectional_iterator<const T, true, Compare>(_ptr); }
			operator T*() { return _ptr; }
		private:
			T* _ptr;
	};
};



#endif
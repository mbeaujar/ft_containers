#ifndef __BIDIRECTIONAL_ITERATOR_HPP__
#define __BIDIRECTIONAL_ITERATOR_HPP__

#include "binary_search_trees.hpp"

namespace ft 
{
	struct bidirectional_iterator_tag {};

	template <typename T, class Compare = ft::less<T> >
	class bidirectional_iterator : private ft::iterator<bidirectional_iterator_tag, T> {
		public:
			typedef typename T::value_type													value_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::pointer			pointer;
			typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::difference_type	difference_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
		
			bidirectional_iterator()
				: _ptr(0)
			{}

			bidirectional_iterator(T *p)
				: _ptr(p)
			{}

			bidirectional_iterator(bidirectional_iterator const &copy)
				: _ptr(copy._ptr)
			{}

			~bidirectional_iterator() {}

			bidirectional_iterator& operator=(bidirectional_iterator const &copy) {
				if (this == &copy)
					return *this;
				_ptr = copy._ptr;
				return *this;
			}

			//bidirectional_iterator

			bool operator==(bidirectional_iterator const &rhs) { return _ptr->data == rhs._ptr->data; }

			bool operator!=(bidirectional_iterator const &rhs) { return _ptr->data != rhs._ptr->data; }

			reference operator*() const { return _ptr->data; }

			pointer operator->() const { return &(operator*()); }

			bidirectional_iterator& operator++() {
				if (_ptr->right) {
					_ptr = _ptr->right;
					while (_ptr->left)
						_ptr = _ptr->left;
				} else {
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
				} else {
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

			//operator bidirectional_iterator<const T>() { return bidirectional_iterator<const T>(_ptr); }
			operator T*() { return _ptr; }
		private:
			T* _ptr;
	};
};



#endif
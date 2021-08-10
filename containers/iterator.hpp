#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <iostream>
#include <iterator>

namespace ft
{

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct iterator
	{
		typedef T				value_type;
		typedef Distance 		difference_type;
		typedef Pointer 		pointer;
		typedef Reference 		reference;
		typedef Category 		iterator_category;
	};

	struct random_access_iterator_tag {};

	/*     template <class Iterator> class iterator_traits;
    template <class T> class iterator_traits<T*>;
    template <class T> class iterator_traits<const T*>; */

	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type 			value_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference 			reference;
		typedef typename Iterator::iterator_category 	iterator_category;
	};

	template <class T>
	struct iterator_traits<T *>
	{
		typedef typename std::ptrdiff_t					difference_type;
		typedef T 										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef typename ft::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T *>
	{
		typedef typename std::ptrdiff_t					difference_type;
		typedef const T 								value_type;
		typedef const T*								pointer;
		typedef const T&								reference;
		typedef typename ft::random_access_iterator_tag	iterator_category;
	};



	template <class Iterator> class reverse_iterator
	{
	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type 			value_type;
		typedef typename iterator_traits<Iterator>::difference_type 	difference_type;
		typedef typename iterator_traits<Iterator>::pointer 			pointer;
		typedef typename iterator_traits<Iterator>::reference 			reference;
	private:
		iterator_type _it;
	public:
		// ------------------ Constructor
		reverse_iterator()
		:
			_it(nullptr)
		{}

		explicit reverse_iterator(iterator_type it)
		:
			_it(it)
		{}

 		template <class Iter> reverse_iterator(const reverse_iterator<Iter>& rev_it) 
		:
			_it(rev_it.base())
		{} 

		//virtual ~reverse_iterator() {}

		// ----------------------------


		iterator_type base() const {
			return _it;
		}

		reference operator*() const {
			iterator_type tmp = _it;
			return *--tmp;
		}

		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(_it - n);
		}

		reverse_iterator& operator++() {
			--_it;
			return *this;
		}

		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			--_it;
			return tmp;
		}

		reverse_iterator& operator+=(difference_type n) {
			_it -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(_it + n);
		}

		reverse_iterator& operator--() {
			++_it;
			return *this;
		}

		reverse_iterator operator--(int) {
			reverse_iterator tmp(*this);
			++_it;
			return tmp;
		}

		bool operator!=(reverse_iterator const &right) {
			return this->base() != right.base();
		}

		reverse_iterator& operator-=(difference_type n) {
			_it += n;
			return *this;
		}

		pointer operator->() const {
			return &(operator*());
		}

		reference operator[](difference_type n) const {
			return base()[-n-1];
		}

	};

	template <typename T>
	class random_access_iterator : private ft::iterator<random_access_iterator_tag, T> 
	{
	public:
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type difference_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category iterator_category;

	private:
		pointer ptr;

	public:
		random_access_iterator()
		:
			ptr(nullptr)
		{}

		random_access_iterator(pointer p)
		:
			ptr(p)
		{}

		~random_access_iterator(){};

		reference  operator*() const {
			return *ptr;
		}

		bool operator!=(random_access_iterator const &right) {
			return ptr != right.ptr;
		}

		bool operator==(random_access_iterator const &right) {
			return ptr == right.ptr;
		}

		random_access_iterator &operator++() {
			++ptr;
			return *this;
		}

		random_access_iterator operator++(int) {
			random_access_iterator tmp(*this);
			++*this;
			return tmp;
		}

		random_access_iterator &operator--() {
			--ptr;
			return *this;
		}

		random_access_iterator operator--(int) {
			random_access_iterator tmp(*this);
			--*this;
			return tmp;
		}
	};

};

#endif
#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <iostream>

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
			: _it(0)
		{}

		explicit reverse_iterator(iterator_type it)
			: _it(it)
		{}

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it)
			: _it(rev_it.base())
		{}

		// ----------------------------


		iterator_type base() const { return _it; }

		reference operator*() const { iterator_type tmp = _it; return *--tmp; }

		reverse_iterator operator+(difference_type n) const { return reverse_iterator(_it - n); }

		reverse_iterator& operator++() { --_it; return *this; }

		reverse_iterator operator++(int) { reverse_iterator tmp = *this; --_it; return tmp; }

		reverse_iterator& operator+=(difference_type n) { _it -= n; return *this; }

		reverse_iterator operator-(difference_type n) const { return reverse_iterator(_it + n); }

		reverse_iterator& operator--() { ++_it; return *this; }

		reverse_iterator operator--(int) { reverse_iterator tmp(*this); ++_it; return tmp; }

		reverse_iterator& operator-=(difference_type n) { _it += n; return *this; }

		pointer operator->() const { return &(operator*()); };

		reference operator[](difference_type n) const { return base()[-n-1]; };


		difference_type operator-(reverse_iterator const &r) { return r.base() - this->base(); }

	};

	template <typename f_T>
	reverse_iterator<f_T> operator+(typename ft::reverse_iterator<f_T>::difference_type n, const reverse_iterator<f_T> &r) { return reverse_iterator<f_T>(n - r.base()); }
	
	template <typename T>
	bool operator==(const reverse_iterator<T> &l, const reverse_iterator<T> &r) { return l.base() == r.base(); };

 	template <typename T, typename U>
	bool operator==(const reverse_iterator<T> &l, const reverse_iterator<U> &r) { return l.base() == r.base(); };

	template <typename T>
	bool operator!=(const reverse_iterator<T> &l, const reverse_iterator<T> &r) { return l.base() != r.base(); };

 	template <typename T, typename U>
	bool operator!=(const reverse_iterator<T> &l, const reverse_iterator<U> &r) { return l.base() != r.base(); };

	template <typename T>
	bool operator<(const reverse_iterator<T> &l, const reverse_iterator<T> &r) { return l.base() > r.base(); };

 	template <typename T, typename U>
	bool operator<(const reverse_iterator<T> &l, const reverse_iterator<U> &r) { return l.base() > r.base(); };

	template <typename T>
	bool operator<=(const reverse_iterator<T> &l, const reverse_iterator<T> &r) { return l.base() >= r.base(); };

 	template <typename T, typename U>
	bool operator<=(const reverse_iterator<T> &l, const reverse_iterator<U> &r) { return l.base() >= r.base(); };

	template <typename T>
	bool operator>(const reverse_iterator<T> &l, const reverse_iterator<T> &r) { return l.base() < r.base(); };

 	template <typename T, typename U>
	bool operator>(const reverse_iterator<T> &l, const reverse_iterator<U> &r) { return l.base() < r.base(); };

	template <typename T>
	bool operator>=(const reverse_iterator<T> &l, const reverse_iterator<T> &r) { return l.base() <= r.base(); };

 	template <typename T, typename U>
	bool operator>=(const reverse_iterator<T> &l, const reverse_iterator<U> &r) { return l.base() <= r.base(); };

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
		pointer _ptr;

	public:
		random_access_iterator()
			: _ptr(0)
		{}

		random_access_iterator(pointer p)
			: _ptr(p)
		{}

		random_access_iterator(random_access_iterator const &copy)
			: _ptr(copy._ptr)
		{}

		random_access_iterator& operator=(random_access_iterator const &copy) {
			if (this == &copy)
				return *this;
			_ptr = copy._ptr;
			return *this;
		}

		// convert iterator non const to iterator const --- solution -> https://www.py4u.net/discuss/133392
		operator random_access_iterator<const T>() {return random_access_iterator<const T>(_ptr);}

		~random_access_iterator(){};


		pointer base() const { return _ptr; }

		reference  operator*() const { return *_ptr; };

		pointer operator->() const { return &(operator*()); };

		reference operator[](difference_type n) const { return *(_ptr + n); };

		random_access_iterator &operator++() { ++_ptr; return *this; }

		random_access_iterator operator++(int) { random_access_iterator tmp(*this); ++*this; return tmp; }

		random_access_iterator &operator--() { --_ptr; return *this; }

		random_access_iterator operator--(int) { random_access_iterator tmp(*this); --*this; return tmp; }

		random_access_iterator operator+(difference_type n) const { return random_access_iterator(_ptr + n); }

		random_access_iterator operator-(difference_type n) const { return random_access_iterator(_ptr - n); }

		random_access_iterator& operator+=(difference_type n) { _ptr += n; return *this; }

		random_access_iterator& operator-=(difference_type n) { _ptr -= n; return *this; }

		//difference_type operator-(const random_access_iterator &r) { return this->base() - r.base(); }
		template <typename f_T, typename f_U>
		friend typename ft::random_access_iterator<f_T>::difference_type operator-(const random_access_iterator<f_T> &l, const random_access_iterator<f_U> &r);

		template <typename f_T>
		friend random_access_iterator<f_T> operator+(typename ft::random_access_iterator<f_T>::difference_type n, const random_access_iterator<f_T> &r);

		template <typename f_T>
		friend random_access_iterator<f_T> operator-(typename ft::random_access_iterator<f_T>::difference_type n, const random_access_iterator<f_T> &r);
	};

	template <typename f_T, typename f_U>
	typename ft::random_access_iterator<f_T>::difference_type operator-(const random_access_iterator<f_T> &l, const random_access_iterator<f_U> &r) { return l.base() - r.base(); }

	template <typename f_T>
	random_access_iterator<f_T> operator+(typename ft::random_access_iterator<f_T>::difference_type n, const random_access_iterator<f_T> &r) { return random_access_iterator<f_T>(r._ptr + n); }

	template <typename f_T>
	random_access_iterator<f_T> operator-(typename ft::random_access_iterator<f_T>::difference_type n, const random_access_iterator<f_T> &r) { return random_access_iterator<f_T>(r._ptr - n); }

 	template <typename T>
	bool operator==(const random_access_iterator<T> &l, const random_access_iterator<T> &r) { return l.base() == r.base(); };

 	template <typename T, typename U>
	bool operator==(const random_access_iterator<T> &l, const random_access_iterator<U> &r) { return l.base() == r.base(); };

	template <typename T>
	bool operator!=(const random_access_iterator<T> &l, const random_access_iterator<T> &r) { return l.base() != r.base(); };

 	template <typename T, typename U>
	bool operator!=(const random_access_iterator<T> &l, const random_access_iterator<U> &r) { return l.base() != r.base(); };

	template <typename T>
	bool operator<(const random_access_iterator<T> &l, const random_access_iterator<T> &r) { return l.base() < r.base(); };

 	template <typename T, typename U>
	bool operator<(const random_access_iterator<T> &l, const random_access_iterator<U> &r) { return l.base() < r.base(); };

	template <typename T>
	bool operator<=(const random_access_iterator<T> &l, const random_access_iterator<T> &r) { return l.base() <= r.base(); };

 	template <typename T, typename U>
	bool operator<=(const random_access_iterator<T> &l, const random_access_iterator<U> &r) { return l.base() <= r.base(); };

	template <typename T>
	bool operator>(const random_access_iterator<T> &l, const random_access_iterator<T> &r) { return l.base() > r.base(); };

 	template <typename T, typename U>
	bool operator>(const random_access_iterator<T> &l, const random_access_iterator<U> &r) { return l.base() > r.base(); };

	template <typename T>
	bool operator>=(const random_access_iterator<T> &l, const random_access_iterator<T> &r) { return l.base() >= r.base(); };

 	template <typename T, typename U>
	bool operator>=(const random_access_iterator<T> &l, const random_access_iterator<U> &r) { return l.base() >= r.base(); };

}

#endif
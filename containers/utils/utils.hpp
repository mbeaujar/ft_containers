#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <iostream>
#include <functional>

namespace ft {


	// ------------ enable_if 

	template<bool B, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	// ----------- is_integral

	template <typename T, bool bool_type>
	struct integral_constant {
		typedef T type;
		const static bool value = bool_type;
	};

	template <class T> struct is_integral : public integral_constant<T, false> {};
	template <> struct is_integral<bool> : public integral_constant<bool, true> {};
	template <> struct is_integral<char> : public integral_constant<char, true> {};
	template <> struct is_integral<wchar_t> : public integral_constant<wchar_t, true> {};
	template <> struct is_integral<signed char> : public integral_constant<signed char, true> {};
	template <> struct is_integral<short int> : public integral_constant<short int, true> {};
	template <> struct is_integral<int> : public integral_constant<int, true> {};
	template <> struct is_integral<long int> : public integral_constant<long int, true> {};
	template <> struct is_integral<long long int> : public integral_constant<long long int, true> {};
	template <> struct is_integral<unsigned char> : public integral_constant<unsigned char, true> {};
	template <> struct is_integral<unsigned short int> : public integral_constant<unsigned short int, true> {};
	template <> struct is_integral<unsigned int> : public integral_constant<unsigned int, true> {};
	template <> struct is_integral<unsigned long int> : public integral_constant<unsigned long int, true> {};
	template <> struct is_integral<unsigned long long int> : public integral_constant<unsigned long long int, true> {};

	// ------------- lexicographical_compare

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

	// -------------------- equal

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	};

	// --------------------- pair

	template<class T1, class T2> struct pair {
		public:

			typedef T1 first_type;
			typedef T2 second_type;

			first_type first;
			second_type second;

			pair()
				: first(),
				  second()
			{}

			template <class U, class V>
			pair(const pair<U, V> &pr)
				: first(pr.first),
				  second(pr.second)
			{}

			pair(const first_type &a, const second_type &b) 
				:	first(a),
					second(b)
			{}

			pair& operator= (const pair& pr) {
				if (this == &pr)
					return *this;
				first = pr.first;
				second = pr.second;
				return *this;
			}
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return !(lhs == rhs); }

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return !(rhs < lhs); }

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return rhs < lhs; }

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return !(lhs < rhs); }

	// ------------------------- make_pair

	template <class T1,class T2>
  	pair<T1,T2> make_pair (T1 x, T2 y)
	{ return pair<T1,T2>(x,y); }

	// ---------------------- less

	template <class T>
    struct less : std::binary_function<T, T, bool>
    {
        bool operator() (const T& x, const T& y) const { return (x < y); }
    };
};

#endif
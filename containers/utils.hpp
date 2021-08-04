#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <iostream>

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
	template <> struct is_integral<char16_t> : public integral_constant<char16_t, true> {};
	template <> struct is_integral<char32_t> : public integral_constant<char32_t, true> {};
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

};

#endif
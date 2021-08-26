#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "../vector/vector.hpp"
#include <iostream>

namespace ft
{

	template <class T, class Container = ft::vector<T> >
	class stack {
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

		// ------------------------------ Member functions

		explicit stack(const container_type &ctnr = container_type())
			: c(ctnr)
		{}

		stack(const stack &other)
			: c(other.c)
		{}

		~stack() {}

		stack &operator=(const stack &other) {
			if (this == &other)
				return *this;
			c = other.c;
			return *this;
		}

		// -------------------------- Element access

		value_type &top() { return c.back(); }

		const value_type &top() const { return c.back(); }

		// -------------------------- Capacity

		bool empty() const { return c.empty(); }

		size_type size() const { return c.size(); }

		// ---------------------------- Modifiers

		void push(const value_type &val) { c.push_back(val); }
		
		void pop() { c.pop_back(); }

		// ---------------------------- Non-member functions

		template <class f_T, class f_Container>
		friend	bool operator==(const stack<f_T, f_Container> &lhs, const stack<f_T, f_Container> &rhs);

		template <class f_T, class f_Container>
		friend bool operator!=(const stack<f_T, f_Container> &lhs, const stack<f_T, f_Container> &rhs);

		template <class f_T, class f_Container>
		friend bool operator<(const stack<f_T, f_Container> &lhs, const stack<f_T, f_Container> &rhs);

		template <class f_T, class f_Container>
		friend bool operator<=(const stack<f_T, f_Container> &lhs, const stack<f_T, f_Container> &rhs);

		template <class f_T, class f_Container>
		friend bool operator>(const stack<f_T, f_Container> &lhs, const stack<f_T, f_Container> &rhs);

		template <class f_T, class f_Container>
		friend bool operator>=(const stack<f_T, f_Container> &lhs, const stack<f_T, f_Container> &rhs);
		
	protected:
		container_type c;
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.c == rhs.c; }

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.c != rhs.c; }

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.c < rhs.c; }

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.c <= rhs.c; }

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.c > rhs.c; }

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return lhs.c >= rhs.c; }

};

#endif
#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <iostream>
#include "../utils/utils.hpp"
#include "../utils/BST.hpp"
#include <memory>

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
	public:
		typedef Key 										key_type;
		typedef T 											mapped_type;
		typedef ft::pair<const key_type, mapped_type> 		value_type;
		typedef Compare 									key_compare;

		class value_compare : std::binary_function<value_type, value_type, bool> {
		public:
			bool operator()( const value_type& lhs, const value_type& rhs ) const
			{ return comp(lhs.first, rhs.first); }
		protected:
			Compare comp;
			value_compare( Compare c ) : comp(c) {}
		};

		typedef Allocator 									allocator_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer 			pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;
	
	private:
		allocator_type _alloc;
		ft::BST<value_type, Compare, allocator_type> _bst;
	};
};

#endif
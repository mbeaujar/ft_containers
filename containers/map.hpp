#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <iostream>
#include "utils.hpp"
#include "binary_search_trees.hpp"
#include <memory>

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		typedef typename ft::binary_search_trees<ft::pair<const Key, T>, Compare>::pointer pointerBST;
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

		typedef Allocator 															allocator_type;
		typedef typename allocator_type::reference 									reference;
		typedef typename allocator_type::const_reference							const_reference;
		typedef typename allocator_type::pointer 									pointer;
		typedef typename allocator_type::const_pointer 								const_pointer;
		typedef typename ft::binary_search_trees<value_type, key_compare>::iterator 		iterator;
		typedef typename ft::binary_search_trees<value_type, key_compare>::const_iterator 	const_iterator;
		// reverse_iterator
		// const_reverse_iterator
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;								

		// ----------------------- Members functions

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			:  _alloc(alloc),
			   _comp(comp),
			   _bst()
		{}

		template <class InputIterator>
  		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			:  _alloc(alloc),
			   _comp(comp),
			   _bst()
		{
			for (; first != last; first++)
				_bst.insert(*first);
		}
	
		map (const map& x)
			:  _alloc(x._alloc),
			   _comp(x._comp),
			   _bst()
		{ _bst = x._bst; }

		~map() {}


		// ------------------------- Iterators

		iterator begin() { return _bst.begin(); }

		const_iterator begin() const { return _bst.begin(); }

		iterator end() { return _bst.end(); }

		const_iterator end() const { return _bst.end(); }

		//reverse_iterator rbegin();
		//const_reverse_iterator rbegin() const;

		//reverse_iterator rend();
		//const_reverse_iterator rend() const;


		// ------------------ Capacity

		bool empty() const { return _bst.empty(); }

		size_type size() const { return _bst.size(); }

		size_type max_size() const { return _bst.max_size(); }


		// ------------------- Element access

		mapped_type& operator[] (const key_type& k) {
			iterator tmp = _bst.search(k);
			if (!tmp)
				tmp = _bst.insert(_bst.begin(), ft::make_pair(k, mapped_type()));
			return tmp->second;
		}

  		pair<iterator,bool> insert (const value_type& val) {
			iterator tmp = _bst.search(val.first);
			if (tmp)
				return ft::make_pair(tmp, false);
			iterator position = _bst.insertNode(_bst.getRoot(), val);
			return ft::make_pair(position, true);
		} 

		iterator insert (iterator position, const value_type& val) { return _bst.insert(position, val); }

		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last) {
			  for (; first != last; ++first)
			  	_bst.insert(_bst.begin(), *first);
		}
    
		void erase (iterator position) {
			_bst.removeNode(position);
		}
	
		size_type erase (const key_type& k) {
			iterator position = _bst.search(k);
			if (!position)
				return 0;
			_bst.removeNode(position);
			return 1;
		}
     	
		void erase (iterator first, iterator last) {
			while (first != last)
				_bst.removeNode(first++);
		}

		void swap(map& x) {
			if (this == &x)
				return;
			allocator_type tmp_alloc 	= x._alloc;
			key_compare tmp_comp 		= x._comp; 
			x._alloc 					= this->_alloc;
			x._comp 					= this->_comp;
			this->_alloc 				= tmp_alloc;
			this->_comp 				= tmp_comp;
			_bst.swap(x._bst);
		}

		void clear() { _bst.clear(); }

		// ----------------------------- Observers

		key_compare key_comp() const { return _comp; }

		value_compare value_comp() const { return value_compare(key_compare()); }

		// --------------------------------- Operations 

		iterator find(const key_type& k) {
			iterator position = _bst.search(k);
			if (!position)
				return _bst.end();
			return position;
		}

		const_iterator find(const key_type& k) const {
			const_iterator position = _bst.search(k);
			if (!position)
				return _bst.end();
			return position;
		}

 		size_type count(const key_type& k) const { return search(k) ? 1 : 0; } 

		iterator lower_bound(const key_type& k) {
			iterator it = _bst.begin();
			iterator ite = _bst.end();
			while (it != ite && _comp(it->first, k))
				it++;
			return it;
		}

		const_iterator lower_bound(const key_type& k) const {
			const_iterator it = _bst.begin();
			const_iterator ite = _bst.end();
			while (it != ite && _comp(it->first, k))
				it++;
			return it;
		}

		iterator upper_bound(const key_type& k) {
			iterator it = _bst.begin();
			iterator ite = _bst.end();
			while (it != ite && _comp(k, it->first) == false)
				it++;
			return it;
		}

		const_iterator upper_bound(const key_type& k) const {
			const_iterator it = _bst.begin();
			const_iterator ite = _bst.end();
			while (it != ite && _comp(k, it->first) == false)
				it++;
			return it;
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const { return ft::make_pair(lower_bound(k), upper_bound(k)); }

		ft::pair<iterator, iterator> equal_range(const key_type& k) { return ft::make_pair(lower_bound(k), upper_bound(k)); }

		// --------------------- Allocator

		allocator_type get_allocator() const { return _bst.get_allocator(); }
		
		// debug
		//void printBST() { _bst.printBST(); }

	private:
		allocator_type 										_alloc;
		key_compare											_comp;
		ft::binary_search_trees<value_type, key_compare> 	_bst;
	};
};

#endif
#ifndef __BINARY_SEARCH_TREES_HPP__
#define __BINARY_SEARCH_TREES_HPP__

#include <iostream>
#include "utils.hpp"
#include "iterator.hpp"
#include "bidirectional_iterator.hpp"

namespace ft 
{
	template <typename T >
	class node {
	public:
		typedef T value_type;
		
		node(value_type const &data, node* left = NULL, node* right = NULL, node* parent = NULL)
			: data(data),
			  left(left),
			  right(right),
			  parent(parent)
		{}

		node(node const &copy) 
			: data(copy.data),
			  left(copy.left),
			  right(copy.right),
			  parent(copy.parent)
		{}


		~node() {};

		node& operator=(node const &copy) {
			if (this == &copy)
				return *this;
			data = copy.data;
			left = copy.left;
			right = copy.right;
			parent = copy.parent;
			return *this;
		}

		value_type data;
		node* left;
		node* right;
		node* parent;
	};

	template <typename T, class Compare = ft::less<T>, class Node = node<T>, class Allocator = std::allocator<Node> >
	class binary_search_trees {
	public:
		typedef T														value_type;
		typedef typename T::first_type									key_type;
		typedef Allocator 												allocator_type;
		typedef Compare 												key_compare;
		typedef Node& 													reference;
		typedef const Node&												const_reference;
		typedef Node*													pointer;
		typedef const Node* 											const_pointer;
		typedef typename allocator_type::difference_type				difference_type;
		typedef typename allocator_type::size_type						size_type;
		typedef typename ft::bidirectional_iterator<Node>				iterator;
		typedef typename ft::bidirectional_iterator<const Node>			const_iterator;


		// --------------------------------------- Members functions

		binary_search_trees(const allocator_type &alloc = allocator_type(), const key_compare &comp = key_compare())
			:  _alloc(alloc),
			   _comp(comp),
			   _size(0)
		{
			_last = _alloc.allocate(1);
			_alloc.construct(_last, Node(T()));
			_root = _last;
		}

		binary_search_trees(const value_type &data, const allocator_type &alloc = allocator_type(), const key_compare &comp = key_compare())
			:  _alloc(alloc),
			   _comp(comp),
			   _size(1)
		{
			_root = _alloc.allocate(1);
			_alloc.construct(_root, Node(data));
			_last = _alloc.allocate(1);
			_alloc.construct(_last, Node(T()));
			_root->right = _last;
		}

		binary_search_trees(binary_search_trees &x)
			: _alloc(x._alloc),
			  _comp(x._comp),
			  _size(0)
		{
			_last = _alloc.allocate(1);
			_alloc.construct(_last, Node(T()));
			_root = _last;
			iterator it = x.begin();
			iterator ite = x.end();
			for (; it != ite; ++it)
				this->insert(*it);
		}

		~binary_search_trees() {
			clearNode(_root);
		}

		binary_search_trees& operator=(binary_search_trees &x) {
			if (this == &x)
				return *this;
			clearNode(_root);
			_last = _alloc.allocate(1);
			_alloc.construct(_last, Node(T()));
			_root = _last;
			_size = 0;
			iterator it = x.begin();
			iterator ite = x.end();
			for (; it != ite; ++it)
				this->insert(*it);
			return *this;
		}

		// ---------------------------- Iterators

		iterator begin() {
			pointer tmp = _root;

			while (tmp->left)
				tmp = tmp->left;
			return iterator(tmp);
		}

		const_iterator begin() const {
			pointer tmp = _root;

			while (tmp->left)
				tmp = tmp->left;
			return const_iterator(tmp);
		}

		iterator end() { return iterator(_last); }

		const_iterator end() const { return const_iterator(_last); }


		// -------------------------------------- Capacity 

		bool empty() const { return _size == 0; }

		size_type size() const { return _size; }

		size_type max_size() const { return allocator_type().max_size(); }

		// ----------------------------------------  Element access

		iterator search(key_type const &n) { return iterator(searchNode(_root, n)); }

		pointer searchNode(pointer root, key_type const &n) {
			if (root == NULL || root == _last)
				return NULL;
			if (root->data.first == n)
				return root;
			if (_comp(n, root->data.first))
				return searchNode(root->left, n);
			return searchNode(root->right, n);
		}
		
		void printBST() { printBST("", _root, false); } 

 		void printBST(std::string prefix, pointer root, bool isLeft)
		{
			if (root != NULL && root != _last)
			{
				std::cout << prefix;
				std::cout << (isLeft ? "├──" : "└──");
				std::cout << root->data.first << std::endl;
				printBST(prefix + (isLeft ? "│   " : "    "), root->left, true);
				printBST(prefix + (isLeft ? "│   " : "    "), root->right, false);
			}
		}
		// ----------------------------------------- Modifiers


		iterator insert(iterator position, const value_type& val) {
			if (_comp(position->first, val.first)) {
				while (_comp(position->first, val.first) && *position != _last->data)
					position++;
				if (position->first == val.first)
					return position;
				return iterator(insertNode(--position, val));
			} else {
				while (_comp(val.first, position->first) && *position != _root->data)
					position--;
				if (position->first == val.first)
					return position;
				return iterator(insertNode(--position, val));
			}
			return position;
		}

		void removeNode(pointer root) {
			if (root == _last || root == NULL)
				return;
			if (root->left == root->right)
				return remove_node_with_no_branch_below(root);
			if (root->left == NULL || root->right == NULL)
				return remove_node_with_one_branch_below(root);
			return remove_node_with_two_branch_below(root);
		}

		pointer insertNode(pointer root, value_type const &n) {
			if (_root == NULL || _root == _last) {
				_root = _alloc.allocate(1);
				_alloc.construct(_root, Node(n));
				_root->right = _last;
				_last->parent = _root;
				_size++;
				return _root;
			}
			if (_comp(n.first, root->data.first)) { 
				if (root->left)
					return insertNode(root->left, n);
				else {
					Node* newNode = _alloc.allocate(1);
					_alloc.construct(newNode, Node(n));
					root->left = newNode;
					newNode->parent = root;
					_size++;
					return newNode;
				}
			}
			else {
				if (root->right && root->right != _last)
					return insertNode(root->right, n);
				else {
					Node* newNode = _alloc.allocate(1);
					_alloc.construct(newNode, Node(n));
					if (root->right == _last) {
						newNode->right = _last;
						_last->parent = newNode;
					}
					root->right = newNode;
					newNode->parent = root;
					_size++;
					return newNode;
				}
			}
		}

		void clearNode(pointer root) {
			if (root == NULL)
				return;
			if (root->left && root != _last)
				clearNode(root->left);
			if (root->right && root != _last)
				clearNode(root->right);
			_size--;
			_alloc.destroy(root);
			_alloc.deallocate(root, 1);
		}

		// --------------------------------------------  Allocator

		allocator_type get_allocator() const { return allocator_type(); }

	private:
		allocator_type 	_alloc;
		pointer 		_root;
		pointer			_last;
		key_compare		_comp;
		size_type		_size;

		void remove_node_with_no_branch_below(pointer root) {
				if (root->parent) {
					if (root->parent->left == root)
						root->parent->left = NULL;
					else
						root->parent->right = NULL;
				}
				if (root == _root)
					_root = _last;
				_size--;
				_alloc.destroy(root);
				_alloc.deallocate(root, 1);
		}

		void remove_node_with_one_branch_below(pointer root) {
				pointer tmp;

				if (root->left == NULL)
					tmp = root->right;
				else
					tmp = root->left;
				if (root->parent) {
					tmp->parent = root->parent;
					if (root->parent->left == root)
						root->parent->left = tmp;
					else
						root->parent->right = tmp;
				}
				else
					tmp->parent = NULL;
				if (root == _root) {
					if (root->left)
						_root = root->left;
					else
						_root = root->right;
				}
				_size--;
				_alloc.destroy(root);
				_alloc.deallocate(root, 1);
		}

		void remove_node_with_two_branch_below(pointer root) {
			pointer tmp = root->right;
			while (tmp->left)
				tmp = tmp->left;
			if (tmp->right) {	// update the branch below and above
				if (tmp->parent->left == tmp)
					tmp->parent->left = tmp->right;
				else
					tmp->parent->right = tmp->right;
				tmp->right->parent = tmp->parent;
			} else {
				if (tmp->parent->left == tmp)
					tmp->parent->left = NULL;
				else
					tmp->parent->right = NULL;
			}
			tmp->left = root->left;
			tmp->right = root->right;
			tmp->parent = root->parent;
			if (tmp->left)
				tmp->left->parent = tmp;
			if (tmp->right)
				tmp->right->parent = tmp;
			if (tmp->parent) {
				if (tmp->parent->left == root)
					tmp->parent->left = tmp;
				if (tmp->parent->right == root)
					tmp->parent->right = tmp;
			}
			else 
				tmp->parent = NULL;
 			if (root == _root)
				_root = tmp;
			_size--;
			_alloc.destroy(root);
			_alloc.deallocate(root, 1);
		}
	};
};


#endif
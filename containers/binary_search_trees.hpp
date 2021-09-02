#ifndef __BINARY_SEARCH_TREES_HPP__
#define __BINARY_SEARCH_TREES_HPP__

#include <iostream>
#include "utils.hpp"
#include "iterator.hpp"

namespace ft 
{

	struct bidirectional_iterator_tag {};

	template <typename T, class Compare = ft::less<T> >
	class BST_iterator : private ft::iterator<bidirectional_iterator_tag, T> {
		public:
			typedef typename T::value_type													value_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::pointer			pointer;
			typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::difference_type	difference_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
		
			BST_iterator()
				: _ptr(0)
			{}

			BST_iterator(T *p)
				: _ptr(p)
			{}

			BST_iterator(BST_iterator const &copy)
				: _ptr(copy._ptr)
			{}

			~BST_iterator() {}

			BST_iterator& operator=(BST_iterator const &copy) {
				if (this == &copy)
					return *this;
				_ptr = copy._ptr;
				return *this;
			}

			//BST_iterator

			bool operator==(BST_iterator const &rhs) { return _ptr->data == rhs._ptr->data; }

			bool operator!=(BST_iterator const &rhs) { return _ptr->data != rhs._ptr->data; }

			reference operator*() const { return _ptr->data; }

			pointer operator->() const { return &(operator*()); }

			BST_iterator& operator++() {
				if (_ptr->right) {
					_ptr = _ptr->right;
					while (_ptr->left)
						_ptr = _ptr->left;
				}
				else
				{
					if (_ptr->parent)
						_ptr = _ptr->parent;
				}
				return *this;
			}
		
		private:
			T* _ptr;
	};

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
		typedef T											value_type;
		typedef Allocator 									allocator_type;
		typedef Compare 									key_compare;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer 			pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename ft::BST_iterator<Node>				iterator;

		binary_search_trees(const allocator_type &alloc = allocator_type(), const key_compare &comp = key_compare())
			:  _alloc(alloc),
			   _comp(comp)
		{
			_last = _alloc.allocate(1);
			_alloc.construct(_last, Node(T()));
			_root = _last;
		}

		binary_search_trees(const value_type &data, const allocator_type &alloc = allocator_type(), const key_compare &comp = key_compare())
			:  _alloc(alloc),
			   _comp(comp)
		{
			_root = _alloc.allocate(1);
			_alloc.construct(_root, Node(data));
			_last = _alloc.allocate(1);
			_alloc.construct(_last, Node(T()));
			_root->right = _last;
		}

		~binary_search_trees() {
			if (_root != _last)
				clearNode(_root);
			else {
				_alloc.destroy(_last);
				_alloc.deallocate(_last, 1);
			}
		}

		void insert(value_type const &n) {
			return insertNode(_root, n);
		}

		pointer search(value_type const &n) {
			return searchNode(_root, n);
		}

		void remove(value_type const &n) {
			if (_root == 0)
				return;
			pointer tmp = searchNode(_root, n);
			if (tmp)
				removeNode(tmp);
		}

		void printTree() {
			printTree("", _root, false);
		}

		bool empty() const {
			return _root == NULL || _root == _last;
		}

		size_type size() const {
			return sizeBST(_root);
		}

		iterator begin() const {
			pointer tmp = _root;

			while (tmp->left)
				tmp = tmp->left;
			return iterator(tmp);
		}

		iterator end() const {
			return iterator(_last);
		}

	private:
		allocator_type 	_alloc;
		pointer 		_root;
		pointer			_last;
		key_compare		_comp;

		size_type sizeBST(pointer root) const {
			if (root == _last || root == NULL)
				return 0;
			return 1 + sizeBST(root->left) + sizeBST(root->right);
		}

 		void printTree(std::string prefix, pointer root, bool isLeft)
		{
			if (root != NULL && root != _last)
			{
				std::cout << prefix;
				std::cout << (isLeft ? "├──" : "└──");
				std::cout << root->data.first << std::endl;
				printTree(prefix + (isLeft ? "│   " : "    "), root->left, true);
				printTree(prefix + (isLeft ? "│   " : "    "), root->right, false);
			}
		}

		pointer searchNode(pointer root, value_type const &n) {
			if (root == NULL || root == _last)
				return NULL;
			if (root->data.first == n.first)
				return root;
			if (n.first < root->data.first)
				return searchNode(root->left, n);
			return searchNode(root->right, n);
		}

		void removeNode(pointer root) {
			if (root == _last || root == NULL)
				return;
			if (root->left == root->right) {  // 0 branch below
				if (root->parent) {
					if (root->parent->left == root)
						root->parent->left = NULL;
					else
						root->parent->right = NULL;
				}
				if (root == _root)
					_root = _last;
				_alloc.destroy(root);
				_alloc.deallocate(root, 1);
				return;
			}
			if (root->left == NULL || root->right == NULL) { // 1 branch below
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
				_alloc.destroy(root);
				_alloc.deallocate(root, 1);
				return;
			} // 2 branch below
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
			_alloc.destroy(root);
			_alloc.deallocate(root, 1);
		}

		void insertNode(pointer root, value_type const &n) {
			if (_root == NULL || _root == _last) {
				_root = _alloc.allocate(1);
				_alloc.construct(_root, Node(n));
				_root->right = _last;
				_last->parent = _root;
				return;
			}
			if (n.first < root->data.first) { // left
				if (root->left)
					insertNode(root->left, n);
				else {
					Node* newNode = _alloc.allocate(1);
					_alloc.construct(newNode, Node(n));
					root->left = newNode;
					newNode->parent = root;
				}
			}
			else { // right
				if (root->right && root->right != _last)
					insertNode(root->right, n);
				else {
					Node* newNode = _alloc.allocate(1);
					_alloc.construct(newNode, Node(n));
					if (root->right == _last) {
						newNode->right = _last;
						_last->parent = newNode;
					}
					root->right = newNode;
					newNode->parent = root;
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
			_alloc.destroy(root);
			_alloc.deallocate(root, 1);
		}
	};
};


#endif
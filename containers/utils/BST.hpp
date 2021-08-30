#ifndef __BST_HPP__
#define __BST_HPP__

#include <iostream>
#include "utils.hpp"
#include <memory>

namespace ft 
{
	template <typename T>
	class Node {
	public:
		typedef T value_type;

		Node(value_type const &node, Node* left = NULL, Node* right = NULL, Node* parent = NULL)
			: _node(node),
			  _left(left),
			  _right(right),
			  _parent(parent)
		{}

		Node(Node const &copy) 
			: _node(copy._node),
			  _left(copy._left),
			  _right(copy._right),
			  _parent(copy._parent)
		{}


		~Node() {};

		Node& operator=(Node const &copy) {
			if (this == &copy)
				return *this;
			_node = copy._node;
			_left = copy._left;
			_right = copy._right;
			_parent = copy._parent;
			return *this;
		}

		value_type getnode() const {
			return _node;
		}

		Node *getleft() const {
			return _left;
		}

		Node *getright() const {
			return _right;
		}

		Node *getparent() const {
			return _parent;
		}

		void setleft(Node* l) {
			_left = l;
		}

		void setright(Node* r) {
			_right = r;
		}

		void setparent(Node* p) {
			_parent = p;
		}
		
	private:
		value_type _node;
		Node* _left;
		Node* _right;
		Node* _parent;
	};

	template <typename T, class Compare = ft::less<T>, class Allocator = std::allocator<ft::Node<T> > >
	class BST {
	public:
		typedef T											value_type;
		typedef ft::Node<value_type> 						Node;
		typedef Compare 									key_compare;
		typedef Allocator 									allocator_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer 			pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;

		BST(const allocator_type &alloc = allocator_type())
			: _alloc(alloc),
			  _root(0)
		{}

		~BST() {
			clearNode(_root);
		}

		void insert(value_type const &n) {
			this->insertNode(_root, n);
		}

		pointer search(value_type const &n) {
			return searchNode(_root, n);
		}

		void remove(value_type const &n) {
			if (_root == NULL)
				return;
			pointer tmp = searchNode(_root, n);
			if (tmp)
				removeNode(tmp);
		}

		void printTree(void) {
			printTree("", _root, false);
		}
	
	private:
		allocator_type _alloc;
		pointer _root;

		void printTree(std::string prefix, pointer root, bool isLeft)
		{
			if (root != NULL)
			{
				std::cout << prefix;

				std::cout << (isLeft ? "├──" : "└──");

				// print the value of the node
				std::cout << root->getnode().first << std::endl;

				// enter the next tree level - left and right branch
				printTree(prefix + (isLeft ? "│   " : "    "), root->getleft(), true);
				printTree(prefix + (isLeft ? "│   " : "    "), root->getright(), false);
			}
		}

		pointer searchNode(pointer root, value_type const &n) {
			if (root == NULL)
				return NULL;
			if (root->getnode().first == n.first)
				return root;
			if (n.first < root->getnode().first)
				return searchNode(root->getleft(), n);
			return searchNode(root->getright(), n);
		}

		void removeNode(pointer root) {
			if (root == NULL)
				return;
			if (root->getleft() == root->getright()) {  // 0 branch below
				if (root->getparent()) {
					if (root->getparent()->getleft() == root)
						root->getparent()->setleft(NULL);
					else
						root->getparent()->setright(NULL);
				}
				if (root == _root)
					_root = NULL;
				_alloc.destroy(root);
				_alloc.deallocate(root, 1);
				return;
			}
			if (root->getleft() == NULL || root->getright() == NULL) { // 1 branch below
				pointer tmp;

				if (root->getleft() == NULL)
					tmp = root->getright();
				else
					tmp = root->getleft();
				if (root->getparent()) {
					tmp->setparent(root->getparent());
					if (root->getparent()->getleft() == root)
						root->getparent()->setleft(tmp);
					else
						root->getparent()->setright(tmp);
				}
				else
					tmp->setparent(NULL);
				if (root == _root) {
					if (root->getleft())
						_root = root->getleft();
					else
						_root = root->getright();
				}
				_alloc.destroy(root);
				_alloc.deallocate(root, 1);
				return;
			} // 2 branch below
			pointer tmp = root->getright();
			while (tmp->getleft())
				tmp = tmp->getleft();
			if (tmp->getright()) {	// update the branch below and above
				if (tmp->getparent()->getleft() == tmp)
					tmp->getparent()->setleft(tmp->getright());
				else
					tmp->getparent()->setright(tmp->getright());
				tmp->getright()->setparent(tmp->getparent());
			} else {
				if (tmp->getparent()->getleft() == tmp)
					tmp->getparent()->setleft(NULL);
				else
					tmp->getparent()->setright(NULL);
			}
			tmp->setleft(root->getleft());
			tmp->setright(root->getright());
			tmp->setparent(root->getparent());
			if (tmp->getleft())
				tmp->getleft()->setparent(tmp);
			if (tmp->getright())
				tmp->getright()->setparent(tmp);
			if (tmp->getparent()) {
				if (tmp->getparent()->getleft() == root)
					tmp->getparent()->setleft(tmp);
				if (tmp->getparent()->getright() == root)
					tmp->getparent()->setright(tmp);
			}
			else 
				tmp->setparent(NULL);
 			if (root == _root)
				_root = tmp;
			std::cout << "to clear: " << root->getnode().first << std::endl;
			std::cout << "new: " << tmp->getnode().first << std::endl;
			_alloc.destroy(root);
			_alloc.deallocate(root, 1);
		}

		void insertNode(pointer root, value_type const &n) {
			if (_root == NULL) {
				_root = _alloc.allocate(1);
				_alloc.construct(_root, Node(n));
				return;
			}
			if (n.first < root->getnode().first) { // left
				if (root->getleft())
					insertNode(root->getleft(), n);
				else {
					Node* newNode = _alloc.allocate(1);
					_alloc.construct(newNode, Node(n));
					root->setleft(newNode);
					newNode->setparent(root);
				}
			}
			else { // right
				if (root->getright())
					insertNode(root->getright(), n);
				else {
					Node* newNode = _alloc.allocate(1);
					_alloc.construct(newNode, Node(n));
					root->setright(newNode);
					newNode->setparent(root);
				}
			}
		}

		void clearNode(pointer root) {
			if (root == NULL)
				return;
			std::cout << "clear: " << root->getnode().first << std::endl;
			if (root->getleft())
				clearNode(root->getleft());
			if (root->getright())
				clearNode(root->getright());
			_alloc.destroy(root);
			_alloc.deallocate(root, 1);
		}

	};

};


#endif
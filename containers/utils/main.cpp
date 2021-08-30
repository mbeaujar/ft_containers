#include "BST.hpp"

int main()
{
	ft::BST<ft::pair<int, int> > a;
	a.insert(ft::pair<int, int>(10, 50));
	a.insert(ft::pair<int, int>(5, 50));
	a.insert(ft::pair<int, int>(15, 50));
	a.insert(ft::pair<int, int>(20, 50));
	a.insert(ft::pair<int, int>(8, 50));
	a.printTree();
/* 	a.remove(ft::pair<int, int>(8, 50));
	a.printTree();
	a.remove(ft::pair<int, int>(15, 50));
	a.printTree(); */
	a.remove(ft::pair<int, int>(10, 50));
	a.printTree();
	//ft::BST<ft::pair<int, int> >::pointer p;
	//a.remove(ft::pair<int, int>(-1, 50));
	std::cout << "---------------" << std::endl;
	ft::BST<ft::pair<int, int> > b;
	b.insert(ft::pair<int, int>(10, 50));
	b.insert(ft::pair<int, int>(20, 50));
	b.insert(ft::pair<int, int>(30, 50));
	b.printTree();
	b.remove(ft::pair<int, int>(10, 50));
	b.printTree();
	b.remove(ft::pair<int, int>(30, 50));
	b.printTree();
	b.remove(ft::pair<int, int>(20, 50));
	b.printTree();

	ft::BST<ft::pair<int, int> >::pointer tmp;
	tmp = b.search(ft::pair<int, int>(10, 50));
	std::cout << tmp << std::endl;
	return 0;
}
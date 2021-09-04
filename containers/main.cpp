#include "binary_search_trees.hpp"
#include "map.hpp"
#include <vector>

/* int main()
{
	ft::BST<ft::pair<int, int> > a;
	a.insert(ft::pair<int, int>(10, 50));
	a.insert(ft::pair<int, int>(5, 50));
	a.insert(ft::pair<int, int>(15, 50));
	a.insert(ft::pair<int, int>(20, 50));
	a.insert(ft::pair<int, int>(8, 50));
	a.printBST();
	a.remove(ft::pair<int, int>(10, 50));
	a.printBST();

	std::cout << "---------------" << std::endl;
	ft::BST<ft::pair<int, int> > b;
	b.insert(ft::pair<int, int>(10, 50));
	b.insert(ft::pair<int, int>(20, 50));
	b.insert(ft::pair<int, int>(30, 50));

	b.printBST();
	b.remove(ft::pair<int, int>(10, 50));
	b.printBST();
	b.remove(ft::pair<int, int>(30, 50));
	b.printBST();
	b.remove(ft::pair<int, int>(20, 50));
	b.printBST();

	ft::BST<ft::pair<int, int> >::pointer tmp;
	tmp = b.search(ft::pair<int, int>(10, 50));
	std::cout << tmp << std::endl;
	return 0;
} */

typedef ft::pair<int, int> value_type;

#include <map>
/* 
int main()
{
	ft::binary_search_trees<value_type> a;
	a.insert(value_type(10, 50));
	a.insert(value_type(5, 50));
	a.insert(value_type(15, 50));
	a.insert(value_type(20, 50));
	a.insert(value_type(8, 50));
	a.printBST();
	a.remove(value_type(5, 50));
	a.printBST();
	ft::binary_search_trees<value_type>::iterator it = a.begin();
	ft::binary_search_trees<value_type>::iterator ite = a.end();
	std::cout << "end: " << ite->first << std::endl;
	for (; it != ite; ++it)
		std::cout << it->first << std::endl;
	std::cout << "------------------------" << std::endl;
	ft::binary_search_trees<value_type>::iterator f = a.begin();
	std::cout << f->first << std::endl;
	std::cout << "------------------------" << std::endl;
	a.printBST();
	return 0;
} */

int main()
{
	ft::map<int, int> a;
	std::map<int, int> b;

	std::cout << a.size() << std::endl;
	std::cout << a.max_size() << std::endl;
	//std::cout << a[0] << std::endl;
/* 	b[0] = 6;
	std::cout << b[0] << std::endl;
	a[0] = 6; */
	std::cout << "-----------" << std::endl;
	std::cout << std::boolalpha <<  "return insert: " << a.insert(value_type(10, 5)).second << std::endl;
	std::cout << a[10] << std::endl;
	std::cout << "-----------" << std::endl;
	ft::map<int, int>::iterator it = a.begin();
	std::cout << a.insert(it, value_type(20, 500))->first << std::endl;
	it = a.begin();
	std::cout << a.insert(it, value_type(5, 500))->first << std::endl;
	ft::map<int, int> c;
	c.insert(a.begin(), a.end());

	std::cout << "------------------" << std::endl;
	ft::map<int, int> d;
	std::cout << d.size() << std::endl;
	d.insert(value_type(50, 20));
	d.insert(value_type(60, 20));
	std::cout << d.size() << std::endl;
	d.erase(d.begin());
	return 0;
}
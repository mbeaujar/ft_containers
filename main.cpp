#include "containers/vector.hpp"

template <typename T>
void printvector(ft::vector<T> a)
{
	typename ft::vector<T>::iterator it;
	int i = 0;
	for (it = a.begin(); it != a.end(); it++, i++)
		std::cout << "#" << i << " " << *it << std::endl;
	std::cout << "size: " << a.size() << std::endl;
	std::cout << "capacity: " << a.capacity() << std::endl;
	std::cout << std::endl;
}

void constructor_vector()
{
	std::cout << "------------- CONSTRUCTOR VECTOR ---------" << std::endl;
	ft::vector<int> a;
	printvector(a);
	ft::vector<int> b(2, 200);
	printvector(b);
	ft::vector<int> c(b.begin(), b.end());
	printvector(c);
	ft::vector<int> d(c);
	printvector(d);
	ft::vector<int> e = d;
	printvector(e);
	ft::vector<int> f;
	f.push_back(10);
	f.push_back(20);
	f.push_back(30);
	f.push_back(40);
	f.push_back(50);
	f.push_back(60);
	printvector(f);
	f.pop_back();
	std::cout << "pop_back ..." << std::endl;
	std::cout << "size: " << f.size() << std::endl;
	std::cout << "capacity: " << f.capacity() << std::endl;
}

void iterator_test()
{
	std::cout << "------------- ITERATOR VECTOR ------------" << std::endl;
	ft::vector<int> a;
	a.push_back(10);
	std::cout << "begin: " << *a.begin() << std::endl;
	std::cout << "end: " << *a.end() << std::endl;
	std::cout << "rbegin: " << *a.rbegin() << std::endl;
	std::cout << "rend: " << *a.rend() << std::endl;
	const ft::vector<int> b(2, 300);
	ft::vector<int>::const_iterator it = b.begin();
	ft::vector<int>::const_iterator ite = b.end();
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
	ft::vector<int>::const_reverse_iterator first = b.rbegin();
	ft::vector<int>::const_reverse_iterator last = b.rend();
	while (first != last)
	{
		std::cout << *first << std::endl;
		first++;
	}
	ft::vector<int> c;
	c.push_back(10);
	c.push_back(20);
	c.push_back(30);
	c.push_back(40);
	ft::vector<int>::reverse_iterator rit = c.rbegin();
	ft::vector<int>::reverse_iterator rite = c.rend();
	while (rit != rite)
	{
		std::cout << *rit << std::endl;
		rit++;
	}
}

int main()
{
	constructor_vector();
	iterator_test();
	return (0);
}
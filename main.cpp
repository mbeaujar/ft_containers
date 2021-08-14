#include "containers/vector.hpp"
#include <iostream>
#include <vector>

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
	//std::cout << "end: " << *a.end() << std::endl;
	std::cout << "rbegin: " << *a.rbegin() << std::endl;
	//std::cout << "rend: " << *a.rend() << std::endl;
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
		if (rit == rite) {
			std::cout << "stop" << std::endl;
			break;
		}
	}

	ft::vector<int> e(1, 200);
	ft::vector<int> f(1, 400);

	ft::vector<int>::iterator efirst = e.begin();
	ft::vector<int>::iterator ffirst = f.begin();
	if (efirst == ffirst)
		std::cout << "a" << std::endl;
	if (efirst != ffirst)
		std::cout << "iterator e is different from b" << std::endl;
	if (efirst > ffirst)
		std::cout << "iterator e is greater than f" << std::endl;
	if (efirst < ffirst)
		std::cout << "iterator e is less than f" << std::endl;
	*efirst = 400;
	if (efirst >= ffirst)
		std::cout << "iterator e ix greater than or equal to f" << std::endl;
	if (efirst <= ffirst)
		std::cout << "iterator e is less than or equal to f" << std::endl;
	ft::vector<int>::reverse_iterator refirst = e.rbegin();
	ft::vector<int>::reverse_iterator rffirst = f.rbegin();
	std::cout << *refirst << std::endl;
	std::cout << *rffirst << std::endl;
	if (refirst == rffirst)
		std::cout << "a" << std::endl;
	if (refirst != rffirst)
		std::cout << "a iterator e is different from b" << std::endl;
	if (refirst > rffirst)
		std::cout << "a iterator e is greater than f" << std::endl;
	if (refirst < rffirst)
		std::cout << "a iterator e is less than f" << std::endl;
	*refirst = 400;
	if (refirst >= rffirst)
		std::cout << "a iterator e ix greater than or equal to f" << std::endl;
	if (refirst <= rffirst)
		std::cout << "a iterator e is less than or equal to f" << std::endl;
	
	{
		ft::vector<int> z(10, 100);
		ft::vector<int>::iterator it = z.begin();
		ft::vector<int>::const_iterator cit = z.begin();
		if (cit == it)
			std::cout << "a" << std::endl;
		if (cit != it)
			std::cout << "b" << std::endl;
		if (cit > it)
			std::cout << "c" << std::endl;
		if (cit >= it)
			std::cout << "d" << std::endl;
		if (cit < it)
			std::cout << "e" << std::endl;
		if (cit <= it)
			std::cout << "f" << std::endl;

		ft::vector<int> w(10, 100);
		ft::vector<int>::reverse_iterator first = w.rbegin();
		ft::vector<int>::const_reverse_iterator cfirst = w.rbegin();
		if (first == cfirst)
			std::cout << "g" << std::endl;
		if (first != cfirst)
			std::cout << "h" << std::endl;
		if (first > cfirst)
			std::cout << "i" << std::endl;
		if (first >= cfirst)
			std::cout << "j" << std::endl;
		if (first < cfirst)
			std::cout << "k" << std::endl;
		if (first <= cfirst)
			std::cout << "l" << std::endl;
	}
}

void resize_test()
{
	std::cout << "------------- RESIZE VECTOR ------------" << std::endl;
	ft::vector<int> a(10);
	printvector(a);
	a.resize(5);
	printvector(a);
	a.resize(10);
	printvector(a);
	a.resize(10);
	printvector(a);

	ft::vector<int> b;
	std::cout << std::boolalpha << "is empty: " << b.empty() << std::endl;
	b.push_back(10);
	std::cout << std::boolalpha << "is empty: " << b.empty() << std::endl;

	ft::vector<int>::size_type sz;

	ft::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	ft::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100); // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		bar.push_back(i);
		if (sz != bar.capacity())
		{
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	try {
	b.reserve(b.get_allocator().max_size() + 1);
	} catch (const std::length_error & le) {
		std::cout << "Length error: " << le.what() << std::endl;
	} 
}

void assign_test()
{
	ft::vector<int> a(3, 400);
	ft::vector<int> b;
	b.assign(a.begin(), a.end());
	printvector(b);
	b.assign(b.begin(), b.begin());
	printvector(b);
	ft::vector<int> c;
	c.assign(1, 100);
	printvector(c);
	c.assign(0, 0);
	printvector(c);
	c.assign(100, 100);
	printvector(c);
	c.assign(-0, 0);
	printvector(c);
}

void pushpop_test()
{
	ft::vector<int> a;
	a.push_back(25);
	a.push_back(35);
	a.push_back(45);
	printvector(a);
	a.pop_back();
	a.pop_back();
	printvector(a);
	a.pop_back();
	/*a.pop_back();
	a.pop_back();
	a.pop_back();
	a.pop_back();
	a.pop_back();*/
	printvector(a);
}

void insert_test()
{
	ft::vector<int> a;

	a.push_back(10);
	a.push_back(20);
	printvector(a);
	a.insert(a.begin(), 25);
	printvector(a);
	a.insert(a.end(), 600);
	printvector(a);
	ft::vector<int> b;
	printvector(b);
	b.insert(b.begin(), 10);
	printvector(b);
	ft::vector<int> c;
	c.insert(c.begin(), 3, 10);
	printvector(c);
	ft::vector<int>::iterator it = c.begin();
	it++;
	it++;
	c.insert(it, 2, 40);
	printvector(c);
	ft::vector<int> d;
	d.insert(d.begin(), c.begin(), c.end());
	printvector(d);

	printvector(a);
	a.insert(a.end(), d.begin(), d.end());
	printvector(a);

	ft::vector<int>::iterator first = a.begin();
	ft::vector<int>::iterator last = a.end();
	first++;
	first++;
	last--;
	last--;
	a.erase(first, last);
	printvector(a);

	ft::vector<int> e;
	e.erase(e.begin(), e.end());
	printvector(e);
	e.push_back(25);
	printvector(e);
	e.erase(e.begin());
	printvector(e);

	printvector(a);
	a.clear();
	printvector(a);

	printvector(b);
	printvector(d);

	b.swap(d);
	printvector(b);
	printvector(d);
}

void operator_test()
{
	ft::vector<int> a;
	ft::vector<int> b;
	if (a == b)
		std::cout << "a and b is equal" << std::endl;
	a.push_back(25);
	if (a != b)
		std::cout << "a and b is not equal" << std::endl;
	if (a > b)
		std::cout << "a is greater than b" << std::endl;
	if (b < a)
		std::cout << "b is less than a" << std::endl;
	if (a >= b)
		std::cout << "a is greater than or equal to b" << std::endl;
	if (b <= a)
		std::cout << "b is less than or equal to a" << std::endl;
	if (a < b)
		std::cout << "a is less than b" << std::endl;
	ft::swap(a, b);
	if (a < b)
		std::cout << "a is less than b" << std::endl;
}


void all_last_test()
{
	ft::vector<int> a(3, 100);
	for (int i = 0; i < 3; i++)
		std::cout << a[i] << std::endl;
	

	// exceptions

	ft::vector<int> b;

	try {
		b.assign(-1, 100);
	} catch (std::exception &e) {
		std::cout << "exc: " << e.what() << std::endl;
	}
	try {
		b.assign(b.get_allocator().max_size() + 1, 100);
	} catch (std::exception &e) {
		std::cout << "exc: " << e.what() << std::endl;
	}
	try {
		b.at(-1);
	} catch (std::exception &e) {
		std::cout << "exc: " << e.what() << std::endl;
	}
	try {
		b.at(b.get_allocator().max_size() + 1);
	} catch (std::exception &e) {
		std::cout << "exc: " << e.what() << std::endl;
	}
	try {
		b.at(10);
	} catch (std::exception &e) {
		std::cout << "exc: " << e.what() << std::endl;
	}
	try {
		b.reserve(b.get_allocator().max_size() + 1);
	} catch (std::exception &e) {
		std::cout << "exc: " << e.what() << std::endl;
	}
}

int main()
{
	constructor_vector();
	iterator_test();
	resize_test();
	assign_test(); 
	pushpop_test();
	insert_test();
	operator_test();
	all_last_test();
	return (0);
}
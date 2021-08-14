#include <vector>
#include <iostream>

 
template <typename T>
void printvector(std::vector<T> a)
{
	typename std::vector<T>::iterator it;
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
	std::vector<int> a;
	printvector(a);
	std::vector<int> b(2, 200);
	printvector(b);
	std::vector<int> c(b.begin(), b.end());
	printvector(c);
	std::vector<int> d(c);
	printvector(d);
	std::vector<int> e = d;
	printvector(e);
	std::vector<int> f;
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
	std::vector<int> a;
	a.push_back(10);
	std::cout << "begin: " << *a.begin() << std::endl;
	//std::cout << "end: " << *a.end() << std::endl;
	std::cout << "rbegin: " << *a.rbegin() << std::endl;
	//std::cout << "rend: " << *a.rend() << std::endl;
	const std::vector<int> b(2, 300);
	std::vector<int>::const_iterator it = b.begin();
	std::vector<int>::const_iterator ite = b.end();
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
	std::vector<int>::const_reverse_iterator first = b.rbegin();
	std::vector<int>::const_reverse_iterator last = b.rend();
	while (first != last)
	{
		std::cout << *first << std::endl;
		first++;
	}
	std::vector<int> c;
	c.push_back(10);
	c.push_back(20);
	c.push_back(30);
	c.push_back(40);
	std::vector<int>::reverse_iterator rit = c.rbegin();
	std::vector<int>::reverse_iterator rite = c.rend();
	while (rit != rite)
	{
		std::cout << *rit << std::endl;
		rit++;
	}
}

void resize_test()
{
	std::cout << "------------- RESIZE VECTOR ------------" << std::endl;
	std::vector<int> a(10);
	printvector(a);
	a.resize(5);
	printvector(a);
	a.resize(10);
	printvector(a);
	a.resize(10);
	printvector(a);

	std::vector<int> b;
	std::cout << std::boolalpha << "is empty: " << b.empty() << std::endl;
	b.push_back(10);
	std::cout << std::boolalpha << "is empty: " << b.empty() << std::endl;

	std::vector<int>::size_type sz;

	std::vector<int> foo;
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

	std::vector<int> bar;
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
	std::vector<int> a(3, 400);
	std::vector<int> b;
	b.assign(a.begin(), a.end());
	printvector(b);
	b.assign(b.begin(), b.begin());
	printvector(b);
	std::vector<int> c;
	c.assign(1, 100);
	printvector(c);
	c.assign(0, 0);
	printvector(c);
}

void pushpop_test()
{
	std::vector<int> a;
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
	a.pop_back(); */
	printvector(a);
}

void insert_test()
{
	std::vector<int> a;

	a.push_back(10);
	a.push_back(20);
	printvector(a);
	a.insert(a.begin(), 25);
	printvector(a);
	a.insert(a.end(), 600);
	printvector(a);
	std::vector<int> b;
	printvector(b);
	b.insert(b.begin(), 10);
	printvector(b);
	std::vector<int> c;
	c.insert(c.begin(), 3, 10);
	printvector(c);
	std::vector<int>::iterator it = c.begin();
	it++;
	it++;
	c.insert(it, 2, 40);
	printvector(c);
	std::vector<int> d;
	d.insert(d.begin(), c.begin(), c.end());
	printvector(d);

	printvector(a);
	a.insert(a.end(), d.begin(), d.end());
	printvector(a);

	std::vector<int>::iterator first = a.begin();
	std::vector<int>::iterator last = a.end();
	first++;
	first++;
	last--;
	last--;
	a.erase(first, last);
	printvector(a);

	std::vector<int> e;
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

int main()
{
	constructor_vector();
	iterator_test();
	resize_test();
	assign_test(); 
	//pushpop_test();
	insert_test();
	return (0);
}
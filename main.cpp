#include <iostream>
#include <vector>
#include <algorithm>

#include "containers/vector.hpp"

void basic()
{
    std::cout << "------ BASIC ---------" << std::endl;
    ft::vector<int> a;
    a.push_back(25);
    a.push_back(35);
    a.push_back(55);
    std::cout << "size: " << a.size() << std::endl;
    ft::vector<int>::iterator it = a.begin();
    ft::vector<int>::iterator ite = a.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;

    std::vector<int> b;
    b.push_back(25);
    b.push_back(35);
    b.push_back(55);
    std::cout << "size: " << b.size() << std::endl;
    std::vector<int>::iterator itb = b.begin();
    std::vector<int>::iterator iteb = b.end();
    for(; itb != iteb; itb++)
        std::cout << *itb << std::endl;
    std::cout << "----------------------" << std::endl;
}

void constructor_with_init_value()
{
    std::cout << "------- INIT VALUE ---------" << std::endl;
    ft::vector<int> a(10, 100);
    ft::vector<int>::iterator it = a.begin();
    ft::vector<int>::iterator ite = a.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;
    std::cout << "----------------------------" << std::endl;

    std::vector<int> b(10, 100);
    std::vector<int>::iterator itb = b.begin();
    std::vector<int>::iterator itbe = b.end();
    for (; itb != itbe; itb++)
        std::cout << *itb << std::endl;
    std::cout << "----------------------------" << std::endl;

	std::cout << "--------- COPY ----------" << std::endl;
	ft::vector<int> c(b.begin(), b.end());
	ft::vector<int>::iterator itc = c.begin();
	ft::vector<int>::iterator itec = c.end();
	for (; itc != itec; itc++)
		std::cout << *itc << std::endl;
}

void reverse_iterator()
{
	ft::vector<int> a;
	a.push_back(15);
	a.push_back(25);
	ft::vector<int>::reverse_iterator ait = a.rbegin();
	ft::vector<int>::reverse_iterator aite = a.rend();
	//std::cout << *ait << std::endl;
	for (; ait != aite; ++ait)
		std::cout << *ait << std::endl;
	std::vector<int> b;
	b.push_back(15);
	b.push_back(25);
	std::vector<int>::reverse_iterator bit = b.rbegin();
	std::vector<int>::reverse_iterator bite = b.rend();
	for (; bit != bite; ++bit)
		std::cout << *bit << std::endl;

}

void printMyvector(ft::vector<int> &a)
{
	int i = 0;
	for (ft::vector<int>::iterator it = a.begin(); it != a.end(); it++, i++)
		std::cout << "#" << i << " " << *it << std::endl;
}

void printRealvector(std::vector<int> &b)
{
	int i = 0;
	for (std::vector<int>::iterator it = b.begin(); it != b.end(); it++, i++)
		std::cout << "#" << i << " " << *it << std::endl;
}

void test_resize()
{
	ft::vector<int> a;
	std::vector<int> b;
	a.push_back(25);
	b.push_back(25);
	std::cout << "before" << std::endl;
	printMyvector(a);
	std::cout << std::endl;
	printRealvector(b);
	a.resize(3, 6);
	b.resize(3, 6);
	std::cout << "after" << std::endl;
	printMyvector(a);
	std::cout << std::endl;
	printRealvector(b);
	try {
		a.reserve(a.max_size() + 1);
	}   catch (const std::length_error& le) {
	  std::cerr << "Length error: " << le.what() << '\n';
  	}
	try {
		b.reserve(b.max_size() + 1);
	}   catch (const std::length_error& le) {
	  std::cerr << "Length error: " << le.what() << '\n';
  	}
}

void test_reserve()
{
	ft::vector<int> a;
	std::vector<int> b;

	std::cout << "len a: " << a.capacity() << std::endl;
	std::cout << "len b: " << b.capacity() << std::endl;
	a.reserve(0);
	b.reserve(0);
	std::cout << "len a: " << a.capacity() << std::endl;
	std::cout << "len b: " << b.capacity() << std::endl;
	a.reserve(10);
	b.reserve(10);
	std::cout << "len a: " << a.capacity() << std::endl;
	std::cout << "len b: " << b.capacity() << std::endl;
	a.reserve(5);
	b.reserve(5);
	std::cout << "len a: " << a.capacity() << std::endl;
	std::cout << "len b: " << b.capacity() << std::endl;
}

void test_insert()
{
	ft::vector<int> a;

	a.push_back(25);
	a.push_back(45);
	ft::vector<int>::iterator iteA = a.begin();
	//iteA++;
	//iteA++;
	a.insert(iteA, 10);
	printMyvector(a);
}

int main()
{
   	//basic();
    //constructor_with_init_value();
    //reverse_iterator();
	//test_resize();
	//test_reserve();
	test_insert();

    return (0);
}
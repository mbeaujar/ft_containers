#include "stack.hpp"
#include <stack>


// test avec un autre container en paramètre dans la template

void test_constructor()
{
	ft::stack<int> a;
	ft::vector<int> container;
	ft::stack<int> b(container);
	//ft::stack<int> b;

	a.push(10);
	std::cout << a.top() << std::endl;
	ft::stack<int> c(a);
	std::cout << c.top() << std::endl;
	c.pop();
	std::cout << a.top() << std::endl;

	b = a;
	std::cout << b.top() << std::endl;
}

void test_operator()
{
	ft::stack<int> a;
	a.push(25);
	ft::stack<int> b(a);
	b.push(50);
	a = b;
	if (a == b)
		std::cout << "a and b are equal" << std::endl;
	if (a != b)
		std::cout << "a and b are not equal" << std::endl;
	if (a > b)
		std::cout << "a is greater than b" << std::endl;
	if (a >= b)
		std::cout << "a is greater than or equal to b" << std::endl;
	if (a < b)
		std::cout << "a is less than b" << std::endl;
	if (a <= b)
		std::cout << "a is less than or equal to b" << std::endl;
	a.pop();
	if (a < b)
		std::cout << "a is less than b" << std::endl;
	if (b > a)
		std::cout << "b is greater than a" << std::endl;
	if (a != b)
		std::cout << "a and b are not equal" << std::endl;
}

void test_elementAccess()
{
	ft::stack<int> a;

	std::cout << a.size() << std::endl;
	std::cout << a.empty() << std::endl;

	a.push(25);
	std::cout << a.top() << std::endl;
	std::cout << a.size() << std::endl;
	std::cout << a.empty() << std::endl;
	const int b = a.top();
	std::cout << b << std::endl;

	a.pop();
	std::cout << a.size() << std::endl;
	std::cout << a.empty() << std::endl;
}

int main()
{
	test_constructor();
	test_operator();
	test_elementAccess();
	return (0);
}
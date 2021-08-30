#include "stack.hpp"
#include <stack>

void test_constructor()
{
	std::stack<int> a;
	std::deque<int> container;
	std::stack<int> b(container);
	//std::stack<int> b;

	a.push(10);
	std::cout << a.top() << std::endl;
	std::stack<int> c(a);
	std::cout << c.top() << std::endl;
	c.pop();
	std::cout << a.top() << std::endl;

	b = a;
	std::cout << b.top() << std::endl;
}

void test_operator()
{
	std::stack<int> a;
	a.push(25);
	std::stack<int> b(a);
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
	std::stack<int> a;

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
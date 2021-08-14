#include <vector>
#include <iostream>
#include "containers/vector.hpp"

int main()
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
	return 0;
}
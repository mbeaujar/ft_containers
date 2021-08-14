#include <vector>
#include <iostream>
#include "containers/vector.hpp"

int main()
{
	try
	{
		ft::vector<int> a;
		a.at(10);
	} catch (std::exception &e) {
		std::cout << "exc: " << e.what() << std::endl;
	}
	return 0;
}
#include <vector>
#include <iostream>
#include "containers/vector.hpp"

int main()
{
	try
	{
		std::vector<int> a;
		a.assign(a.get_allocator().max_size() + 1, 100);
	} catch (std::exception &e) {
		std::cout << "exc: " << e.what() << std::endl;
	}
	return 0;
}
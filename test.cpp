#include "containers/vector.hpp"
#include <vector>

int main()
{
    ft::vector<int> a;
    a[0] = 10;
    std::cout << "size: " << a.size() << std::endl;
    ft::vector<int>::iterator it = a.begin();
    std::cout << *it << std::endl;


    std::vector<int> b;
    b[0] = 10;
    std::cout << "size: " << b.size() << std::endl;
    std::vector<int>::iterator itb = b.begin();
    std::cout << *itb << std::endl;
	return (0);
}
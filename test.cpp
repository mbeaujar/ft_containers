//#include "containers/vector.hpp"
#include <vector>
#include <iostream>


typedef size_t value_type;

std::string sto_string(value_type n)
{
    std::string ret = "";
    if (n == 0) {
        ret = "0";
        return ret;
    }
    while (n > 0)
    {
        ret.insert(ret.begin(), (n % 10) + 48);
        n /= 10;
    }
    return ret;
}

int main()
{
/*      ft::vector<int> a;
    a.push_back(25);
    ft::vector<int>::iterator it = a.begin();
    std::cout << *it << std::endl;  */
    value_type n = -1;

    std::cout << sto_string(n) << std::endl;


    /*
    ft::vector<int> a;
    a[0] = 10;
    std::cout << "size: " << a.size() << std::endl;
    ft::vector<int>::iterator it = a.begin();
    std::cout << *it << std::endl;


    std::vector<int> b;
    b[0] = 10;
    std::cout << "size: " << b.size() << std::endl;
    std::vector<int>::iterator itb = b.begin();
    std::cout << *itb << std::endl;*/
	return (0);
}
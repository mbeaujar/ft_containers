#include <iostream>
#include <vector>
#include <algorithm>

#include "vector/vector.hpp"

int main()
{
    ft::vector<int> a;
    a.push_back(25);
    a.push_back(35);
    std::cout << "size: " << a.size() << std::endl;
    ft::vector<int>::iterator it = a.begin();
    ft::vector<int>::iterator ite = a.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;

    std::vector<int> b;
    b.push_back(25);
    b.push_back(35);
    std::cout << "size: " << b.size() << std::endl;
    std::vector<int>::iterator itb = b.begin();
    std::vector<int>::iterator iteb = b.end();
    for(; itb != iteb; itb++)
        std::cout << *itb << std::endl;

    return (0);
}
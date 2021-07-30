#include <iostream>
#include <vector>
#include <algorithm>

#include "vector/vector.hpp"

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
}


int main()
{
    basic();
    constructor_with_init_value();
    return (0);
}
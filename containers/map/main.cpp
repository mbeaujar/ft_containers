#include <iostream>
#include <map>


int main()
{
	std::map<int, std::string> a;
	a.insert(std::pair<int, std::string>(5, "test"));
	a.insert(std::pair<int, std::string>(10, "test1"));
	a.insert(std::pair<int, std::string>(20, "test2"));
	a.insert(std::pair<int, std::string>(25, "test3"));
	a.insert(std::pair<int, std::string>(0, "test4"));
	std::map<int, std::string>::iterator it;
	for (it = a.begin(); it != a.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	return 0;
}
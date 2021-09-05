#include "binary_search_trees.hpp"
#include "map.hpp"
#include <map>

/* int main()
{
	ft::map<int, int> a;

	a.insert(ft::make_pair(10, 5));
 	a.insert(ft::make_pair(5, 5));
	a.insert(ft::make_pair(8, 5));
	a.insert(ft::make_pair(12, 5));
	//a.printBST();
	a.insert(ft::make_pair(15, 5));
	a.insert(ft::make_pair(13, 5));
	a.insert(ft::make_pair(14, 5));
	a.insert(ft::make_pair(20, 5));
	a.insert(ft::make_pair(19, 5));
	a.insert(ft::make_pair(50, 5));
	a.insert(ft::make_pair(0, 5));
	
	
	//a.printBST();
	int i = 0;
 	ft::map<int, int>::iterator it = a.begin();
	ft::map<int, int>::iterator ite = a.end();
 	for (; it != ite; i++, it++)
		std::cout << it->first << std::endl;
	
	std::cout << "--------------------------" << std::endl;

	it = a.begin();
	ite = a.end();
	--ite;
	for (; i > 0; --ite, i--)
		std::cout << ite->first << std::endl;

	a.clear();
  	a.insert(a.begin(), ft::make_pair(10, 5));
	std::cout << a.begin()->first << std::endl; 
	std::cout << "erase: " << a.erase(10) << std::endl;
	std::cout << "erase: " << a.erase(10) << std::endl;
	std::cout << "erase: " << a.erase(10) << std::endl;
	a.erase(a.begin(), a.end());
	a.clear();
	a.insert(ft::make_pair(10, 5));
	a.insert(ft::make_pair(8, 5));
	a.insert(ft::make_pair(5, 5));
	a.insert(ft::make_pair(28, 5));
	a.insert(ft::make_pair(12, 5));
	std::cout << "size: " << a.size() << std::endl;
	//a.erase(a.begin(), a.end());
	ite = a.end();
	--ite;
	a.erase(a.begin(), ite);
	std::cout << "size a: " << a.size() << std::endl;
	ft::map<int, int> b;
	std::cout << "size b: " << b.size() << std::endl;
	b.swap(a);
	std::cout << "size a: " << a.size() << std::endl;
	std::cout << "size b: " << b.size() << std::endl;
	std::cout << b[28] << std::endl;
	std::cout << b.max_size() << std::endl;
	std::cout << b.get_allocator().max_size() << std::endl;
	a.clear();
	a.insert(ft::make_pair(10, 5));
	a.insert(ft::make_pair(8, 5));
	a.insert(ft::make_pair(5, 5));
	a.insert(ft::make_pair(28, 5));
	a.insert(ft::make_pair(12, 5));
	std::cout << a.lower_bound(8)->first << std::endl;
	return 0;
} */

int upper_bound_lower_bound()
{
 	ft::map<char,int> mymap;
  ft::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  std::cout << "ici: " << itup->first << std::endl;
  std::cout << "ici: " << itlow->first << std::endl;
  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

int equal_range()
{
  ft::map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';

  return 0;
}
/* 
int key_comp()
{
  ft::map<char,int> mymap;

  ft::map<char,int>::key_compare mycomp = mymap.key_comp();

  mymap['a']=100;
  mymap['b']=200;
  mymap['c']=300;

  std::cout << "mymap contains:\n";

  char highest = mymap.rbegin()->first;     // key value of last element

  ft::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mycomp((*it++).first, highest) );

  std::cout << '\n';

  return 0;
} */
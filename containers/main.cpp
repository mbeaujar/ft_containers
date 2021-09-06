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

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};


int constructor()
{
  std::map<char,int> first;

  first['a']=10;
  first['b']=30;
  first['c']=50;
  first['d']=70;

  std::map<char,int> second (first.begin(),first.end());

  std::map<char,int> third (second);

  std::map<char,int,classcomp> fourth;                 // class as Compare

  bool(*fn_pt)(char,char) = fncomp;
  std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

  return 0;
}

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
} 

int value_comp()
{
  ft::map<char,int> mymap;

  mymap['x']=1001;
  mymap['y']=2002;
  mymap['z']=3003;

  std::cout << "mymap contains:\n";

  ft::pair<char,int> highest = *mymap.rbegin();          // last element

  ft::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mymap.value_comp()(*it++, highest) );

  return 0;
}


int find()
{
  ft::map<char,int> mymap;
  ft::map<char,int>::iterator it;

  mymap['a']=50;
  mymap['b']=100;
  mymap['c']=150;
  mymap['d']=200;

  it = mymap.find('b');
  if (it != mymap.end())
    mymap.erase (it);

  // print content:
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';

  return 0;
}

int count()
{
  ft::map<char,int> mymap;
  char c;

  mymap ['a']=101;
  mymap ['c']=202;
  mymap ['f']=303;

  for (c='a'; c<'h'; c++)
  {
    std::cout << c;
    if (mymap.count(c)>0)
      std::cout << " is an element of mymap.\n";
    else 
      std::cout << " is not an element of mymap.\n";
  }

  return 0;
}

int clear()
{
  ft::map<char,int> mymap;

  mymap['x']=100;
  mymap['y']=200;
  mymap['z']=300;

  std::cout << "mymap contains:\n";
  for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  mymap.clear();
  mymap['a']=1101;
  mymap['b']=2202;

  std::cout << "mymap contains:\n";
  for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

int swap()
{
  ft::map<char,int> foo,bar;

  foo['x']=100;
  foo['y']=200;

  bar['a']=11;
  bar['b']=22;
  bar['c']=33;

  foo.swap(bar);

  std::cout << "foo contains:\n";
  for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "bar contains:\n";
  for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

int erase()
{
  ft::map<char,int> mymap;
  ft::map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

  it=mymap.find('b');
  mymap.erase (it);                   // erasing by iterator

  mymap.erase ('c');                  // erasing by key

  it=mymap.find ('e');
  mymap.erase ( it, mymap.end() );    // erasing by range

  // show content:
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}


int insert()
{
  ft::map<char,int> mymap;

  // first insert function version (single parameter):
  mymap.insert ( ft::pair<char,int>('a',100) );
  mymap.insert ( ft::pair<char,int>('z',200) );

  ft::pair<ft::map<char,int>::iterator,bool> ret;
  ret = mymap.insert ( ft::pair<char,int>('z',500) );
  if (ret.second==false) {
    std::cout << "element 'z' already existed";
    std::cout << " with a value of " << ret.first->second << '\n';
  }

  // second insert function version (with hint position):
  ft::map<char,int>::iterator it = mymap.begin();
  mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
  mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

  // third insert function version (range insertion):
  ft::map<char,int> anothermap;
  anothermap.insert(mymap.begin(),mymap.find('c'));

  // showing contents:
  std::cout << "mymap contains:\n";
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "anothermap contains:\n";
  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}

int operator_access_element()
{
  ft::map<char,std::string> mymap;

  mymap['a']="an element";
  mymap['b']="another element";
  mymap['c']=mymap['b'];

  std::cout << "mymap['a'] is " << mymap['a'] << '\n';
  std::cout << "mymap['b'] is " << mymap['b'] << '\n';
  std::cout << "mymap['c'] is " << mymap['c'] << '\n';
  std::cout << "mymap['d'] is " << mymap['d'] << '\n';

  std::cout << "mymap now contains " << mymap.size() << " elements.\n";

  return 0;
}

int empty ()
{
  ft::map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  while (!mymap.empty())
  {
    std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
    mymap.erase(mymap.begin());
  }

  return 0;
}
int operator_assignation()
{
  ft::map<char,int> first;
  //ft::map<char,int> second;

  first['x']=8;
  first['y']=16;
  first['z']=32;

  ft::map<char, int> second=first;                // second now contains 3 ints
  first=ft::map<char,int>();  // and first is now empty

  {
    ft::map<char, int> third = second;
    std::cout << "Size of third: " << third.size() << '\n';
  }

  std::cout << "Size of first: " << first.size() << '\n';
  std::cout << "Size of second: " << second.size() << '\n';
  return 0;
}

int main()
{
/*   ft::map<int, int> a;
  
  a.insert(a.begin(), ft::make_pair(10, 5));
  a.insert(a.end(), ft::make_pair(8, 5));
  a.insert(ft::make_pair(9, 5));
  a.insert(ft::make_pair(80, 5));
  a.insert(ft::make_pair(80, 5));
  a.insert(a.begin(), a.end());
  a.insert(a.begin(), ft::make_pair(15, 5));

  ft::map<int, int>::iterator it = a.begin();
  ft::map<int, int>::iterator ite = a.end();
  for (; it != ite; it++)
    std::cout << it->first << std::endl;
  std::cout << a.size() << std::endl;
   it = a.begin();
  --ite;
  for (; it != ite; ite--)
    std::cout << ite->first << std::endl;
  a.erase(10);
  a.erase(a.begin());
  a.erase(a.begin(), a.end());
  std::cout << a.size() << std::endl;
  constructor();
  upper_bound_lower_bound();
  equal_range();
  key_comp();
  value_comp();
  find();
  count();
  clear();
  swap();
  erase();
  insert();
  operator_access_element();
  empty(); */
  operator_assignation();
  return 0;
}

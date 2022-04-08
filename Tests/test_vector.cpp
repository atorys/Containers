//
// Created by Achiote Tory on 4/8/22.
//
#include "../Sources/vector.hpp"
#include <iostream>
#define NAME	ft

//template < class T >
//void	init_vector(NAME::vector<T>* vector) {
//	std::srand(time(0));
//
//}

void test_vector()
{

	char ch, carr[] = "abc";

	NAME::vector<char>::allocator_type	*p_alloc	= (std::allocator<char> *)0;
	NAME::vector<char>::pointer			p_ptr		= (char *)0;
	NAME::vector<char>::const_pointer		p_cptr		= (const char *)0;
	NAME::vector<char>::reference			p_ref		= ch;
	NAME::vector<char>::const_reference	p_cref		= (const char&)ch;
	NAME::vector<char>::value_type		*p_val		= (char *)0;
	NAME::vector<char>::size_type			*p_size		= (size_t *)0;
	NAME::vector<char>::difference_type	*p_diff		= (ptrdiff_t *)0;
	(void) p_cref;
	(void) p_val;
	(void) p_ptr;
	(void) p_diff;
	(void) p_size;
	(void) p_cptr;
	(void) p_alloc;
	(void) p_ref;



	NAME::vector<char> vector;
	std::allocator<char> al = vector.get_allocator();


	NAME::vector<char> v0a(al);

	assert(vector.empty() && vector.size() == 0);
	assert(v0a.size() == 0 && v0a.get_allocator() == al);


	NAME::vector<char> v1(5);


	NAME::vector<char> v1a(6, 'x');


	NAME::vector<char> v1b(7, 'y', al);

	assert(v1.size() == 5);

	assert(v1.back() == '\0');

	assert(v1a.size() == 6 && v1a.back() == 'x');
	assert(v1b.size() == 7 && v1b.back() == 'y');


	NAME::vector<char> v2(v1a);
	assert (v2.size() == 6 && v2.front() == 'x');


	NAME::vector<char> v3(v1a.begin(), v1a.end());
	assert(v3.size() == 6 && v3.front() =='x');


	NAME::vector<char>	v4(v1a.begin(), v1a.end());
	assert(v4.size() == 6 && v4.back() == 'x');


	vector = v4;
	assert(vector.size() == 6 && vector.at(5) == 'x');
	assert(vector[0] == 'x' && vector.at(5) == 'x');


	vector.reserve(12);
	assert(12 <= vector.capacity());


	vector.resize(8);
	assert (vector.size() == 8);
	assert (vector.back() == '\0');


	vector.resize(10, 'z');
	assert(vector.size() == 10 && vector.back() == 'z');
	assert(vector.size() <= vector.max_size());

	NAME::vector<char>::iterator		 			p_it(vector.begin());
//	NAME::vector<char>::const_iterator			p_cit(v4.begin());
	NAME::vector<char>::reverse_iterator 			p_rit(vector.rbegin());
//	NAME::vector<char>::const_reverse_iterator 	p_crit(v4.rbegin());


	assert(*p_it == 'x' && *--(p_it = vector.end()) == 'z');
//	assert(*p_cit == 'x' && *--(p_cit = v4.end()) == 'x');

	assert(*p_rit == 'z' && *--(p_rit = vector.rend()) == 'x');
//	assert(*p_crit == 'x' && *--(p_crit = v4.rend()) == 'x');

//	assert(vector.front() == 'x' && v4.front() == 'x');


	vector.push_back('a');
	assert(vector.back() == 'a');

	vector.pop_back();
//	assert(vector.back() == 'z' && v4.back() == 'x');

//	vector.assign(v4.begin(), v4.end());
//	assert(vector.size() == v4.size());
//	assert(vector.front() == v4.front());
//
//	vector.assign(4, 'w');
	assert(vector.size() == 4 && vector.front() == 'w');



	assert(*vector.insert(vector.begin(), 'a') == 'a');
	assert(vector.front() == 'a' && *++vector.begin() == 'w');

	vector.insert(vector.begin(), 2, 'b');
	assert(vector.front() == 'b' && *++vector.begin() == 'b' && *(++(++vector.begin())) == 'a');

//	vector.insert(vector.end(), v4.begin(), v4.end());
//	assert(vector.back() == v4.back());

	vector.insert(vector.end(), carr, carr + 3);
	assert(vector.back() == 'c');

	vector.erase(vector.begin());
	assert(vector.front() == 'b' && *++vector.begin() == 'a');

	vector.erase(vector.begin(), ++vector.begin());
	assert(vector.front() == 'a');
	vector.clear();
	assert(vector.empty());

	vector.swap(v1);
	assert(!vector.empty() && v1.empty());

	assert(v1 == v1 && vector > v1);
	assert(vector != v1 && v1 < vector);
	assert(vector >= v1 && v1 <= vector && v1 >= v1 && vector <= vector);

	NAME::vector<NAME::pair<int, char>, std::allocator<NAME::pair<int, char> > > pair;

	pair.insert(pair.begin(), NAME::make_pair(4, 'a'));

	NAME::vector<NAME::pair<int, char>, std::allocator<ft::pair<int, char> > >::iterator itp(pair.begin());

	assert(itp->first == 4 && itp->second == 'a') ;
	try
	{
		pair.at(10);
		std::cout << "No exception is thrown" << std::endl;
		assert(false);
	}
	catch(...)
	{
		assert(true);
	}
}


int main()
{
	test_vector();

	return (0);
}
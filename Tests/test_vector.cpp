//
// Created by Achiote Tory on 4/8/22.
//
#include "../Sources/vector.hpp"
#include <iostream>
#include <deque>
#include <list>
#include <vector>

#include "../Sources/stack.hpp"
#include "../Sources/map.hpp"
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
	NAME::vector<char>::const_iterator				p_cit(v4.begin());
	NAME::vector<char>::reverse_iterator 			p_rit(vector.rbegin());
	NAME::vector<char>::const_reverse_iterator 		p_crit(v4.rbegin());


	assert(*p_it == 'x' && *--(p_it = vector.end()) == 'z');
	assert(*p_cit == 'x' && *--(p_cit = v4.end()) == 'x');

	assert(*p_rit == 'z' && *--(p_rit = vector.rend()) == 'x');
	assert(*p_crit == 'x' && *--(p_crit = v4.rend()) == 'x');

	assert(vector.front() == 'x' && v4.front() == 'x');


	vector.push_back('a');
	assert(vector.back() == 'a');

	vector.pop_back();
	assert(vector.back() == 'z' && v4.back() == 'x');

	vector.assign(v4.begin(), v4.end());
	assert(vector.size() == v4.size());
	assert(vector.front() == v4.front());

	vector.assign(4, 'w');
	assert(vector.size() == 4 && vector.front() == 'w');



	assert(*vector.insert(vector.begin(), 'a') == 'a');
	assert(vector.front() == 'a' && *++vector.begin() == 'w');

	vector.insert(vector.begin(), 2, 'b');
	assert(vector.front() == 'b' && *++vector.begin() == 'b' && *(++(++vector.begin())) == 'a');

	vector.insert(vector.end(), v4.begin(), v4.end());
	assert(vector.back() == v4.back());

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

void	test_stack() {
	typedef std::allocator<char> Myal;
	typedef std::deque<char, Myal>	Myimpl;
	typedef std::list<char, Myal>	Myimpl2;
	typedef std::vector<char, Myal>	Myimpl3;

	typedef ft::stack<char, Myimpl> Mycont;
	typedef ft::stack<char, Myimpl2> Mycont2;
	typedef ft::stack<char, Myimpl3> Mycont3;

	Mycont v0(Myimpl(3, 'x')), v0a;
	Mycont2 v1;
	Mycont3 v2;
	assert(v0.size() == 3 && v0.top() == 'x');
	assert(v0a.empty());
	v0 = v0a;
	v0.push('a');
	assert(v0.size() == 1 && v0.top() == 'a');
	v0.push('b');
	assert(v0.size() == 2 && v0.top() == 'b');
	v0.push('c');
	assert(v0.size() == 3 && v0.top() == 'c');
	assert(v0 == v0 && v0a < v0);
	assert(v0 != v0a && v0 > v0a);
	assert(v0a <= v0 && v0 >= v0a);
	v0.pop();
	assert(v0.top() == 'b');
	v0.pop();
	assert(v0.top() == 'a');
	v0.pop();
	assert(v0.empty());

	ft::stack<int> stack;
	ft::stack<int> stack1;

	assert(stack1.empty());
	for (int i = 0; i < 30; i++)
		stack1.push(i);
	assert(!stack1.empty());
	assert(stack1.size() == 30);
	stack.swap(stack1);
	assert(stack1.empty());

	while (!stack.empty()) {
		std::cout << stack.top() << " ";
		stack.pop();
	}
	assert(stack.empty());
	std::cout << std::endl;
}

void test_map() {
	typedef std::less<char> Mypred;
	typedef ft::pair<const char, int> Myval;
	typedef std::allocator<Myval> Myal;
	typedef ft::map<char, int, Mypred, Myal> Mycont;


	Myval x, xarr[3], xarr2[3];

	for (int i = 0; i < 3; ++i) {
		new(&xarr[i])Myval('a' + i, 1 + i);
		new(&xarr2[i])Myval('d' + i, 4 + i);
	}
	Mycont v0;
	Myal al = v0.get_allocator();
	Mypred pred;
	Mycont v0a(pred), v0b(pred, al);

	assert(v0.empty() && v0.size() == 0);
	assert(v0a.size() == 0 && v0a.get_allocator() == al);
	assert(v0b.size() == 0 && v0b.get_allocator() == al);

	Mycont v1(xarr, xarr + 3);
	assert(v1.size() == 3 && (*v1.begin()).first == 'a');

	Mycont v2(xarr, xarr + 3, pred);
	assert(v2.size() == 3 && (*v2.begin()).first == 'a');

	Mycont v3(xarr, xarr + 3, pred, al);
	assert(v3.size() == 3 && (*v3.begin()).first == 'a');

	const Mycont v4(xarr, xarr + 3);
	assert(v4.size() == 3 && (*v4.begin()).first == 'a');
	v0 = v4;
	assert(v0.size() == 3 && (*v0.begin()).first == 'a');

	assert(v0.size() <= v0.max_size());

	Mycont::iterator p_it(v1.begin());
	Mycont::const_iterator p_cit(v4.begin());
	Mycont::reverse_iterator p_rit(v1.rbegin());
	Mycont::const_reverse_iterator p_crit(v4.rbegin());
	assert((*p_it).first == 'a' && (*p_it).second == 1
		   && (*--(p_it = v1.end())).first == 'c');
	printf("1\n");
	assert((*p_cit).first == 'a'
		   && (*--(p_cit = v4.end())).first == 'c');

	assert((*p_rit).first == 'c' && (*p_rit).second == 3
		   && (*--(p_rit = v1.rend())).first == 'a');
	printf("2\n");
	assert((*p_crit).first == 'c'
		   && (*--(p_crit = v4.rend())).first == 'a');
	printf("3\n");
	v0.clear();
	ft::pair<Mycont::iterator, bool> pib = v0.insert(Myval('d', 4));
	assert((*pib.first).first == 'd' && pib.second);
	assert((*--v0.end()).first == 'd');
	pib = v0.insert(Myval('d', 5));
	assert((*pib.first).first == 'd'
		   && (*pib.first).second == 4 && !pib.second);
	assert((*v0.insert(v0.begin(), Myval('e', 5))).first == 'e');

	v0.insert(xarr, xarr + 3);
	assert(v0.size() == 5 && (*v0.begin()).first == 'a');
	v0.insert(xarr2, xarr2 + 3);
	assert(v0.size() == 6 && (*--v0.end()).first == 'f');
	assert(v0['c'] == 3);

	assert((*v0.erase(v0.begin())).first == 'b'
		   && v0.size() == 5);
	assert((*v0.erase(v0.begin(), ++v0.begin())).first == 'c'
		   && v0.size() == 4);
	assert(v0.erase('x') == 0 && v0.erase('e') == 1);

	v0.clear();
	assert(v0.empty());
	v0.swap(v1);
	assert(!v0.empty() && v1.empty());
	ft::swap(v0, v1);
	assert(v0.empty() && !v1.empty());
	assert(v1 == v1 && v0 < v1);
	assert(v0 != v1 && v1 > v0);
	assert(v0 <= v1 && v1 >= v0);
	assert(v0.key_comp()('a', 'c') && !v0.key_comp()('a', 'a'));
	assert(v0.value_comp()(Myval('a', 0), Myval('e', 0))
		   && !v0.value_comp()(Myval('a', 0), Myval('a', 1)));
	assert((*v4.find('b')).first == 'b');
	assert(v4.count('x') == 0 && v4.count('b') == 1);
	assert((*v4.lower_bound('a')).first == 'a');
	assert((*v4.upper_bound('a')).first == 'b');
	ft::pair<Mycont::const_iterator, Mycont::const_iterator> pcc
			= v4.equal_range('a');
	assert((*pcc.first).first == 'a' && (*pcc.second).first == 'b');
}


int main()
{
	test_vector();
	test_stack();
	test_map();
	printf("3\n");

	return (0);
}
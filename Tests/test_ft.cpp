//
// Created by Achiote Tory on 4/8/22.
//
#include <iostream>
#include <deque>
#include <map>
#include <list>
#include <vector>
#include "../Sources/vector.hpp"
#include "../Sources/stack.hpp"
#include "../Sources/map.hpp"
#include "../Sources/set.hpp"

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs)
	{
		this->_c = rhs._c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->_c.begin(); }
	iterator end() { return this->_c.end(); }
};


void test_vector()
{
	std::cout << "--------------------------TEST-VECTOR--------------------------\n";
	std::cout << "TEST 1 assert\n";
	{
		char ch, carr[] = "abc";

		ft::vector<char>::allocator_type *p_alloc = (std::allocator<char> *) 0;
		ft::vector<char>::pointer p_ptr = (char *) 0;
		ft::vector<char>::const_pointer p_cptr = (const char *) 0;
		ft::vector<char>::reference p_ref = ch;
		ft::vector<char>::const_reference p_cref = (const char &) ch;
		ft::vector<char>::value_type *p_val = (char *) 0;
		ft::vector<char>::size_type *p_size = (size_t *) 0;
		ft::vector<char>::difference_type *p_diff = (ptrdiff_t *) 0;
		(void) p_cref;
		(void) p_val;
		(void) p_ptr;
		(void) p_diff;
		(void) p_size;
		(void) p_cptr;
		(void) p_alloc;
		(void) p_ref;


		ft::vector<char> vector;
		std::allocator<char> al = vector.get_allocator();


		ft::vector<char> v0a(al);

		assert(vector.empty() && vector.size() == 0);
		assert(v0a.size() == 0 && v0a.get_allocator() == al);


		ft::vector<char> v1(5);


		ft::vector<char> v1a(6, 'x');


		ft::vector<char> v1b(7, 'y', al);

		assert(v1.size() == 5);

		assert(v1.back() == '\0');

		assert(v1a.size() == 6 && v1a.back() == 'x');
		assert(v1b.size() == 7 && v1b.back() == 'y');


		ft::vector<char> v2(v1a);
		assert (v2.size() == 6 && v2.front() == 'x');


		ft::vector<char> v3(v1a.begin(), v1a.end());
		assert(v3.size() == 6 && v3.front() == 'x');


		ft::vector<char> v4(v1a.begin(), v1a.end());
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

		ft::vector<char>::iterator p_it(vector.begin());
		ft::vector<char>::const_iterator p_cit(v4.begin());
		ft::vector<char>::reverse_iterator p_rit(vector.rbegin());
		ft::vector<char>::const_reverse_iterator p_crit(v4.rbegin());


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

		ft::vector<ft::pair<int, char>, std::allocator<ft::pair<int, char> > > pair;

		pair.insert(pair.begin(), ft::make_pair(4, 'a'));

		ft::vector<ft::pair<int, char>, std::allocator<ft::pair<int, char> > >::iterator itp(pair.begin());

		assert(itp->first == 4 && itp->second == 'a');
		try {
			pair.at(10);
			std::cout << "No exception is thrown" << std::endl;
			assert(false);
		}
		catch (...) {
			assert(true);
		}
	}
	std::cout << "SUCCESS testing vector\n";
}

void	test_stack() {

	std::cout << "--------------------------TEST-STACK--------------------------\n";
	std::cout << "TEST 1 assert\n";
	{
		typedef std::allocator<char> Myal;
		typedef std::deque<char, Myal> Myimpl;
		typedef std::list<char, Myal> Myimpl2;
		typedef std::vector<char, Myal> Myimpl3;

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
		std::cout << "-------------------------\n";
	}
	std::cout << "TEST 2 iterable stack\n";
	{
		MutantStack<char> iterable_stack;
		for (char letter = 'a'; letter <= 'z'; letter++)
			iterable_stack.push(letter);
		for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
		{
			std::cout << *it;
		}
		std::cout << std::endl;
		std::cout << "-------------------------\n";
	}
	std::cout << "TEST 3 inner containers\n";
	{
		ft::stack<int, std::deque<int> > stack_deq_buffer;
	}
	std::cout << "SUCCESS testing stack\n";
}

void test_map() {
	std::cout << "--------------------------TEST-MAP--------------------------\n";
	std::cout << "TEST 1 assert\n";
	{
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
		assert((*p_cit).first == 'a'
			   && (*--(p_cit = v4.end())).first == 'c');

		assert((*p_rit).first == 'c' && (*p_rit).second == 3
			   && (*--(p_rit = v1.rend())).first == 'a');
		assert((*p_crit).first == 'c'
			   && (*--(p_crit = v4.rend())).first == 'a');
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
		std::cout << "-------------------------\n";
	}
	std::cout << "TEST 2 constructor\n\n";
	{
		ft::map<int, std::string >	v0;
		std::cout << "empty map created size=" << v0.size() << " maxsize=" << v0.max_size() << "\n";
		for (int i = 0; i < 100; i++)
			v0.insert(ft::make_pair(i, std::to_string(i)));
		std::cout << "fill map newsize=" << v0.size() << "\n";

		ft::map<int, std::string>	v0a(v0);
		assert(v0 == v0a);
		std::cout << "copy map created size=" << v0a.size() << " maxsize=" << v0a.max_size() << "\n\n";

		std::cout << "...erasing copy to check deep copying...\n";
		v0a.erase(v0a.begin(), v0a.end());
		std::cout << "after erasing copy_size=" << v0a.size() << " original map size=" << v0.size() << "\n\n";

		ft::map<int, std::string>	v0b = v0;
		std::cout << "assigning map created size=" << v0b.size() << " maxsize=" << v0b.max_size() << "\n";
		assert(v0 == v0b);
		std::cout << "...erasing original map to check deep copying...\n";
		v0.erase(v0.begin(), v0.end());
		std::cout << "after erasing copy_size=" << v0b.size() << " original map size=" << v0.size() << "\n\n";

		v0b = v0;
		std::cout << "assigning empty map to copy\n";
		std::cout << "after assigning copy_size=" << v0b.size() << "\n\n";
		std::cout << "-------------------------\n";
	}
	std::cout << "TEST 3 capacity\n\n";
	{
		ft::map<int, int >	v0;
		std::cout << "empty map created size=" << v0.size();
		std::cout << " empty=" << (v0.empty() ? "true" : "false") << "\n";

		for (int i = 0; i < 1000; i += 2)
			v0.insert(ft::make_pair(i, i + i % 4));

		std::cout << "filled map newsize=" << v0.size();
		std::cout << " empty=" << (v0.empty() ? "true" : "false") << "\n";

		for (int i = 1; i < 1000; i += 2)
			v0.insert(ft::make_pair(i, i + i % 4));
		std::cout << "filled map newsize=" << v0.size();
		std::cout << " empty=" << (v0.empty() ? "true" : "false") << "\n";

		std::cout << "-------------------------\n";
	}
	std::cout << "TEST 4 access and iterators\n\n";
	{
		ft::map<int, int >	v0;

		for (int i = 0; i < 20; i += 2)
			v0.insert(ft::make_pair(i, i + i % 4));

		std::cout << "created non empty map, random access iterator \n";
		std::cout << "forward iteration : ";
		ft::map<int, int >::iterator	it = v0.begin();
		for (; it != v0.end(); ++it)
			std::cout << it->first << " ";
		std::cout << "\nbackward iteration : ";
		--it;
		for (; it != --v0.begin(); --it)
			std::cout << it->first << " ";
		std::cout << "\n";

		std::cout << "iteration with reverse iterator \n";
		std::cout << "forward iteration : ";
		ft::map<int, int >::reverse_iterator	it2 = v0.rbegin();
		for (; it2 != v0.rend(); ++it2)
			std::cout << it2->first << " ";
		std::cout << "\nbackward iteration : ";
		--it2;
		for (; it2 != v0.rbegin(); --it2)
			std::cout << it2->first << " ";
		std::cout << "\n";

		std::cout << "access with at() : ";
		try {
			std::cout << v0.at(0);
			std::cout << v0.at(2);
			std::cout << v0.at(16);
			std::cout << v0.at(356);
			std::cout << v0.at(12345);
		}
		catch (...) {
			std::cout << "exception thrown\n";
		}

		std::cout << "access with operator[] : ";
		std::cout << v0[0];
		std::cout << v0[2];
		std::cout << v0[16];
		std::cout << v0[356];
		std::cout << v0[12345];
		std::cout << "\n";

		std::cout << "-------------------------\n";
	}
	std::cout << "TEST 5 modifiers\n\n";
	{
		ft::map<char, char >	v0;
		ft::map<char, char >	v0a;
		ft::map<char, char >	v0b;

		std::cout << "first insertion with insert(VALUE) \n";
		for (int i = 0; i < 100; i += 3) {
			std::cout << (v0.insert(ft::make_pair(i, i + i % 2)).second ? "+" : "-");
		}
		std::cout << "\nrepeated insertion with insert(VALUE) \n";
		for (int i = 0; i < 100; i += 2) {
			std::cout << (v0.insert(ft::make_pair(i, i + i % 2)).second ? "+" : "-");
		}
		std::cout <<"\n";

		std::cout << "insert(FIRST, LAST) \n";
		v0a.insert(v0.begin(), v0.end());
		std::cout << (v0 == v0a ? "true" : "false");
		std::cout <<"\n";

		std::cout << "insert(ITER, VALUE) \n";
		for (int i = 38; i < 88; ++i)
			std::cout << v0a.insert(v0a.begin(), ft::make_pair(i, i))->first;
		std::cout <<"\n";

		std::cout << "erase() min element before_size=" << v0a.size() << "\n";
		v0a.erase((++v0a.begin())->first);
		try {
			std::cout << v0b.at((++v0a.begin())->first);
		}
		catch (...) {
			std::cout << "element was erased after_size=" << v0a.size() << "\n\n";
		}

		v0b = v0a;
		std::cout << "erase(FIRST, LAST) before_size=" << v0b.size() << "\n";
		v0b.erase(v0b.begin(), v0b.end());
		std::cout << "elements were erased after_size=" << v0b.size() << "\n\n";

		std::cout << "before clear() size=" << v0a.size() << "\n";
		v0a.clear();
		std::cout << "after clear() size=" << v0a.size() << "\n";

		std::cout << "-------------------------\n";
	}
	std::cout << "TEST 6 look up\n\n";
	{
		ft::map<char, char >	v0;
		ft::map<char, char >	v0a;
		ft::map<char, char >	v0b;

		for (int i = 0; i < 100; i += 3) {
			std::cout << (v0.insert(ft::make_pair(i, i + i % 2)).second ? "+" : "-");
		}
		std::cout << "\n find(): ";
		std::cout << v0.find(33)->first;
		std::cout << v0.find(99)->first;
		std::cout << v0.find(66)->first;
		std::cout << v0.find(60)->first;
		std::cout << v0.find(63)->first;

		std::cout << "\n count(): ";
		for (int i = 23; i < 120; i++)
			std::cout << v0.count(i);
		std::cout << "\n";
		std::cout << "-------------------------\n";
	}
	std::cout << "SUCCESS testing map\n";
}

void test_set()
{
	std::cout << "--------------------------TEST-SET--------------------------\n";
	std::cout << "TEST 1 assert\n";
	{
		typedef std::allocator<char> Myal;
		typedef std::less<char> Mypred;
		typedef ft::set<char, Mypred, Myal> Mycont;
		char str1[] = "abc", str2[] = "def";

		Mycont v0;
		Myal al = v0.get_allocator();
		Mypred pred;
		Mycont v0a(pred), v0b(pred, al);

		assert(v0.empty() && v0.size() == 0);
		assert(v0a.size() == 0 && v0a.get_allocator() == al);
		assert(v0b.size() == 0 && v0b.get_allocator() == al);

		Mycont v1(str1, str1 + 3);
		assert(v1.size() == 3 && *v1.begin() == 'a');
		Mycont v2(str1, str1 + 3, pred);
		assert(v2.size() == 3 && *v2.begin() == 'a');
		Mycont v3(str1, str1 + 3, pred, al);
		assert(v3.size() == 3 && *v3.begin() == 'a');
		const Mycont v4(str1, str1 + 3);
		v0 = v4;
		assert(v0.size() == 3 && *v0.begin() == 'a');

		Mycont::iterator p_it(v1.begin());
		Mycont::const_iterator p_cit(v4.begin());
		Mycont::reverse_iterator p_rit(v1.rbegin());
		Mycont::const_reverse_iterator p_crit(v4.rbegin());
		assert(*p_it == 'a' && *--(p_it = v1.end()) == 'c');
		assert(*p_cit == 'a' && *--(p_cit = v4.end()) == 'c');
		assert(*p_rit == 'c' && *--(p_rit = v1.rend()) == 'a');
		assert(*p_crit == 'c' && *--(p_crit = v1.rend()) == 'a');

		v0.clear();
		ft::pair<Mycont::iterator, bool> pib = v0.insert('d');
		assert(*pib.first == 'd' && pib.second);
		assert(*--v0.end() == 'd');
		pib = v0.insert('d');
		assert(*pib.first == 'd' && !pib.second);
		assert(*v0.insert(v0.begin(), 'e') == 'e');
		v0.insert(str1, str1 + 3);
		assert(v0.size() == 5 && *v0.begin() == 'a');
		v0.insert(str2, str2 + 3);
		assert(v0.size() == 6 && *--v0.end() == 'f');
		assert(*v0.erase(v0.begin()) == 'b');
		assert(v0.size() == 5);
		assert(*v0.erase(v0.begin(), ++v0.begin()) == 'c' && v0.size() == 4);
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
		assert(v0.value_comp()('a', 'c') && !v0.value_comp()('a', 'a'));
		assert(*v4.find('b') == 'b');
		assert(v4.count('x') == 0 && v4.count('b') == 1);
		assert(*v4.lower_bound('a') == 'a');
		assert(*v4.upper_bound('a') == 'b');
		ft::pair<Mycont::const_iterator, Mycont::const_iterator> pcc = v4.equal_range('a');
		assert(*pcc.first == 'a' && *pcc.second == 'b');
	}
	std::cout << "TEST 2 constructor\n\n";
	{
		ft::set<int, std::greater<int> >	v0;
		ft::set<int, std::less<int> >		v2;

		std::cout << "empty set created size=" << v0.size() << "\n";
		for (int i = 0; i < 5; i++)
			v0.insert(i);
		std::cout << "fill set newsize=" << v0.size() << "\n\n";

		std::cout << "creating set with different Compare function\n";
		v2.insert(v0.begin(), v0.end());
		std::cout << "first element of set<GREATER>: " << *v0.begin() << "\n";
		std::cout << "first element of set<LESS>: " << *v2.begin() << "\n\n";

		ft::set<int, std::greater<int> >	v0a(v0);
		assert(v0 == v0a);
		std::cout << "copy set created size=" << v0a.size() << "\n\n";

		std::cout << "...erasing copy to check deep copying...\n";
		v0a.erase(v0a.begin(), v0a.end());
		std::cout << "after erasing copy_size=" << v0a.size() << " original set size=" << v0.size() << "\n\n";

		ft::set<int, std::greater<int> >	v0b = v0;
		std::cout << "assigning set created size=" << v0b.size() << "\n";
		assert(v0 == v0b);
		std::cout << "...erasing set to check deep copying...\n";
		v0b.erase(v0b.begin(), v0b.end());
		std::cout << "after erasing copy_size=" << v0b.size() << " original set size=" << v0.size() << "\n\n";

		v0 = v0b;
		std::cout << "assigning empty set to original set\n";
		std::cout << "after assigning copy_size=" << v0.size() << "\n\n";
		std::cout << "-------------------------\n";
	}
	std::cout << "TEST 3 capacity\n\n";
	{
		ft::set<std::string>	v0;
		std::cout << "empty map created size=" << v0.size();
		std::cout << " empty=" << (v0.empty() ? "true" : "false") << "\n";

		for (int i = 0; i < 10000; i += 2)
			v0.insert(std::to_string(i));

		std::cout << "filled map newsize=" << v0.size();
		std::cout << " empty=" << (v0.empty() ? "true" : "false") << "\n";

		for (int i = 0; i < 10000; i++)
			v0.insert(std::to_string(i));
		std::cout << "filled map newsize=" << v0.size();
		std::cout << " empty=" << (v0.empty() ? "true" : "false") << "\n";

		std::cout << "-------------------------\n";
	}
	std::cout << "TEST 4 access and iterators\n\n";
	{
		ft::set<int>	v0;

		for (int i = 0; i < 20; i += 2)
			v0.insert(i);

		std::cout << "created non empty map, random access iterator \n";
		std::cout << "forward iteration : ";
		ft::set<int>::iterator	it = v0.begin();
		for (; it != v0.end(); ++it)
			std::cout << *it << " ";
		std::cout << "\nbackward iteration : ";
		--it;
		for (; it != --v0.begin(); --it)
			std::cout << *it << " ";
		std::cout << "\n";

		std::cout << "iteration with reverse iterator \n";
		std::cout << "forward iteration : ";
		ft::set<int>::reverse_iterator	it2 = ++v0.rbegin();
		for (; it2 != v0.rend(); ++it2)
			std::cout << *it2 << " ";
		std::cout << "\nbackward iteration : ";
		--it2;
		for (; it2 != v0.rbegin(); --it2)
			std::cout << *it2 << " ";
		std::cout << "\n";

		std::cout << "-------------------------\n";
	}
	std::cout << "TEST 5 modifiers\n\n";
	{
		ft::set<char>	v0;
		ft::set<char>	v0a;
		ft::set<char>	v0b;

		std::cout << "first insertion with insert(VALUE) \n";
		for (int i = 0; i < 100; i += 3) {
			std::cout << (v0.insert(i).second ? "+" : "-");
		}
		std::cout << "\nrepeated insertion with insert(VALUE) \n";
		for (int i = 0; i < 100; i += 2) {
			std::cout << (v0.insert(i).second ? "+" : "-");
		}
		std::cout <<"\n";

		std::cout << "insert(FIRST, LAST) \n";
		v0a.insert(v0.begin(), v0.end());
		std::cout << (v0 == v0a ? "true" : "false");
		std::cout <<"\n";

		std::cout << "insert(ITER, VALUE) \n";
		for (int i = 38; i < 88; ++i)
			std::cout << *v0a.insert(v0a.begin(), i);
		std::cout <<"\n";

		std::cout << "erase() min element before_size=" << v0a.size() << "\n";
		v0a.erase(*(++v0a.begin()));
		std::cout << "element was erased after_size=" << v0a.size() << "\n\n";

		v0b = v0a;
		std::cout << "erase(FIRST, LAST) before_size=" << v0b.size() << "\n";
		v0b.erase(v0b.begin(), v0b.end());
		std::cout << "elements were erased after_size=" << v0b.size() << "\n\n";

		std::cout << "before clear() size=" << v0a.size() << "\n";
		v0a.clear();
		std::cout << "after clear() size=" << v0a.size() << "\n";

		std::cout << "-------------------------\n";
	}
	std::cout << "TEST 6 look up\n\n";
	{
		ft::set<char >	v0;
		ft::set<char >	v0a;
		ft::set<char >	v0b;

		for (int i = 0; i < 100; i += 3) {
			std::cout << ((v0.insert((char)i)).second ? "+" : "-");
		}
		std::cout << "\n find(): ";
		std::cout << *v0.find(33);
		std::cout << *v0.find(99);
		std::cout << *v0.find(66);
		std::cout << *v0.find(60);
		std::cout << *v0.find(63);

		std::cout << "\n count(): ";
		for (int i = 23; i < 120; i++)
			std::cout << v0.count(i);
		std::cout << "\n";
		std::cout << "-------------------------\n";
	}
	std::cout << "SUCCESS testing set\n";
}

int main()
{
	test_vector();
	test_stack();
	test_map();
	test_set();

	return (0);
}
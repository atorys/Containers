//
// Created by atory on 3/12/22.
//

#include <iostream>
#include <vector>
#include <map>
#include "cstdio"
#include "Sources/vector.hpp"
#include "Sources/stack.hpp"
#include "Sources/Tree/tree.hpp"
#include "Sources/map.hpp"

int main()
{
//	ft::vector<int>::iterator	iterator;
//	ft::vector<int>::iterator	iterator2;
//	ft::vector<int> vector(0);
//
////	vector.insert(vector.begin(), 1);
//	vector.push_back(1);
//	vector.push_back(2);
//	vector.push_back(3);
//	vector.push_back(4);
//	vector.push_back(5);
//	vector.push_back(6);
//	vector.push_back(7);
//	vector.push_back(8);
//	vector.push_back(9);
//	iterator = vector.begin();
//	iterator2 = vector.end();
//	for (; iterator != iterator2 ; ++iterator) {
//		std::cout << *iterator << std::endl;
//	}
//	vector.erase(vector.begin() + 1);
//	printf("\n\n");
//	iterator = vector.begin();
//	iterator2 = vector.end();
//	for (; iterator != iterator2 ; ++iterator) {
//		std::cout << *iterator << std::endl;
//	}
//
//	ft::stack<int> stack(vector);
//	ft::stack<int> stack2;
//
//	stack2 = stack;
//	std::cout << stack2.top();
//	stack2.pop();
//	stack2.pop();
//	std::cout << stack2.top();

//	ft::vector<int> vector(0);
//	std::cout << vector.size() << std::endl;
//	std::cout << vector.capacity()<< std::endl;
//	vector.resize(1000, 42);
//	std::cout << vector.size() << std::endl;
//	std::cout << vector.capacity();

	{

		ft::RedBlackTree< ft::RedBlackTreeTraits<int, std::greater<int> > >	tree;
		ft::map<const int, int> tree2;

		tree2.insert(ft::make_pair(12, 234));
		tree2.insert(ft::make_pair(85, 56));
		tree2.insert(ft::make_pair(107, 56));
		tree2.insert(ft::make_pair(8, 56));
		tree2.insert(ft::make_pair(15, 56));
		tree2.insert(ft::make_pair(15, 78));
		tree2.insert(ft::make_pair(78, 56));
//		tree2.insert(ft::make_pair(4, 56));
		tree2.insert(ft::make_pair(9, 56));
		tree2.insert(ft::make_pair(99, 56));
		tree2.insert(ft::make_pair(100, 56));
		tree2.insert(ft::make_pair(101, 56));
		tree2.insert(ft::make_pair(758, 56));
		tree2.insert(ft::make_pair(9, 56));
		tree2.insert(ft::make_pair(8, 94));
//		std::vector<int> v;
//
//		for (int i = 0, j = 10; i < 30 * 2; ++i, ++j) {
//			tree2.insert(ft::make_pair(i, j));
//		}
//		ft::map<int, int> mp2(tree2.begin(), tree2.end());
//		ft::map<int, int>::iterator it = mp2.begin();
//		for (int i = 0; i < 30 * 2; ++i, it++) {
//			v.push_back(it->first);
//			v.push_back(it->second);
//		}
//		return v;

		ft::RedBlackTree< ft::RedBlackTreeTraits< ft::pair<const int, int>, std::less<int> > >::iterator it;
//		ft::RedBlackTree< ft::RedBlackTreeTraits< ft::pair<const int, int>, std::greater<int> > >::iterator it2;
////		ft::pair<ft::RedBlackTree< ft::RedBlackTreeTraits< ft::pair<const int, int>, std::greater<int> > >::iterator, ft::RedBlackTree< ft::RedBlackTreeTraits< ft::pair<const int, int>, std::greater<int> > >::iterator> rt = tree2.equal_range(2);
		tree2.print();
		it = tree2.begin();
//		it2 = tree.begin();
		for (; it != tree2.end(); ++it) {
			std::cout << it->first << "\n";
		}

		--it;
		for (; it != tree2.end(); --it) {
			std::cout << it->first << "\n";
		}
//

//		std::vector<int> v;
//
//		for (int i = 0, j = 10; i < 30 * 2; ++i, ++j) {
//			tree2.insert(ft::make_pair(i, j));
//		}

//		mp.insert(ft::make_pair(45, 3));
//		mp.insert(ft::make_pair(1, 3));
//		mp.insert(ft::make_pair(8, 3));
//		mp.insert(ft::make_pair(5, 3));

//		std::vector<int> v;
//		for (int i = 0, j = 10; i < 20 * 2; ++i, ++j)
//			mp.insert(ft::make_pair(i, j));
//		ft::map<const int, int> mp2;
//		for (int i = 20 * 2, j = 200010; i < 40 * 2; ++i, ++j)
//			mp2.insert(ft::make_pair(i, j));
//		mp2 = mp;
//		ft::map<const int, int>::iterator it = mp2.begin();
//		for (; it != mp2.end(); it++) {
//			std::cout << it->first;
//		}

//		tree2.erase(8);
//		tree2.print();


//		ft::RedBlackTree< ft::RedBlackTreeTraits< ft::pair<const int, int>, std::greater<int> > >::reverse_iterator it;

//		it = tree2.rend();
//		std::cout << (*(*it)).first;
//		tree2.print();
//		tree.insert(10);
//		tree.insert(11);
//		tree.print();
//		tree.print();
//		tree.insert(10);
//		tree.insert(6);
//		tree.insert(45);
//		tree.insert(4);
//		tree.insert(8);
//		tree.insert(0);
//		tree.insert(25);
//		tree.insert(15);
//		tree.insert(22);
//		tree.insert(6);
//		tree.print();
//
//		std::cout << tree.at(10);

//		std::cout << tree.size() << "\n";
//		tree.insert(33);
//		std::cout << tree.size() << "\n";

//		std::cout << *tree.find(45) << "\n";
//		std::cout << tree.count(45) << "\n";
//		std::cout << tree.count(99) << "\n";

//		ft::RedBlackTree< ft::RedBlackTreeTraits<int, std::greater<int> > >::iterator	it;
//		it = tree.begin();
//		for (; it != tree.end(); ++it)
//			std::cout << *(it) << "\n";
//
//		--it;
//		for (; it != tree.end(); --it)
//			std::cout << *(it) << "\n";

//		ft::map<int, std::string> map;
//		ft::map<int, std::string, std::greater<int> > map2;
//		ft::map<int, std::string, std::greater<int> >::iterator it2;
//		std::map<int, int> map2;

//		it2	= map2.begin();
//
//		map2.insert(ft::make_pair(1, "34"));
//		map.insert(ft::make_pair(3, "97"));
//		map.insert(ft::make_pair(0, "2"));
//
//		map.begin();
//		std::cout << map.max_size() << "\n";
//		ft::map<int, std::string>::iterator	it;
//		it = map.begin();
//		for (; it != map.end(); ++it)
//			std::cout << (*it).first << "\n";
//
//		--it;
//		for (; it != map.end(); --it)
//			std::cout << (*it).first << "\n";
//
//		ft::map<int, std::string> map2;
//		map2 = map;
//
//		it = map2.begin();
//		for (; it != map2.end(); ++it)
//			std::cout << (*it).first << "\n";

//		std::vector<int> v;
//		return v;
	}

	while (1)
	{}
	return 0;
}
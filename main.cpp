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
		ft::RedBlackTree< ft::RedBlackTreeTraits<int, std::less<int>, std::allocator<int> > >	tree;

		tree.insert(10);
		tree.insert(11);
//		tree.print();
		tree.print();
////		tree.insert(10);
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

//		std::cout << tree.size() << "\n";
//		tree.insert(33);
//		std::cout << tree.size() << "\n";

//		ft::RedBlackTree<int>::iterator	it;
//		it = tree.begin();
//		for (; it != tree.end(); ++it)
//			std::cout << *(it) << "\n";


		ft::map<int, int> map;
		std::map<int, int> map2;

//		map.ins
//
////		map.begin();
		std::cout << map.max_size() << "\n";
		std::cout << map2.max_size() << "\n";

	}
//	while (1)
//	{}
	return 0;
}
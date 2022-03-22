//
// Created by atory on 3/12/22.
//

#include "iostream"
#include <vector>
#include "Sources/vector.hpp"

int main()
{
	ft::vector<int>::iterator	iterator;
	ft::vector<int>::iterator	iterator2;
	ft::vector<int> vector(4, 15);
	ft::vector<int> vector2(2);
	ft::vector<int> vector3;

//	vector.insert(vector.begin(), 3, 4);
	vector.push_back(3);
	vector.push_back(4);
	vector.push_back(5);
//	vector.pop_back();
	iterator = vector.begin();
	iterator2 = vector.end();
	for (; iterator != iterator2 ; ++iterator) {
		std::cout << *iterator << std::endl;
	}
//	vector2 = vector;
//	vector2.insert(vector2.begin(), 4);
//	iterator = vector2.begin();
//	iterator2 = vector2.end();
//	for (; iterator != iterator2 ; ++iterator) {
//		std::cout << *iterator << std::endl;
//	}
	return 0;
}
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

	iterator = vector2.begin();
	iterator2 = vector2.end();
	for (; iterator != iterator2 ; ++iterator) {
		std::cout << *iterator << std::endl;
	}
	vector2 = vector;
	iterator = vector2.begin();
	iterator2 = vector2.end();
	for (; iterator != iterator2 ; ++iterator) {
		std::cout << *iterator << std::endl;
	}
	return 0;
}
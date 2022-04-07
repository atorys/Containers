//
// Created by Achiote Tory on 4/6/22.
//

#include "../Sources/map.hpp"

void	test_insert(int size)
{
	ft::map<int, std::string>	map;
	std::cout << size << " elements insertion :\n";

	for (int i = 1; i < size; i += 2)
	{
		map.insert(ft::pair<int, std::string>(i, std::to_string(i) + "_"));
	}
	std::cout << "size :" << map.size() << "\n";
	std::cout << "same values insertion :\n";
	for (int i = 0; i < size; i++)
	{
		map.insert(ft::pair<int, std::string>(i, std::to_string(i) + "_"));
	}
	std::cout << "size :" << map.size() << "\n";

	ft::map<int, std::string>::iterator 	it = map.begin();
	for (; it != map.end(); ++it)
		std::cout << it->first << " ";
	std::cout << "\n\n";
}

void test_size() {
	ft::map<int, int>	map;

	std::cout << "map creation	size() = " << map.size() << "\n";
	std::cout << "				max_size() = " << map.max_size() << "\n";
	for (int i = 1; i < 785; i += 45)
		map.insert(ft::pair<int, int>(i,  i * 7));
	std::cout << "after insertion	size() = " << map.size() << "\n";
	std::cout << "					max_size() = " << map.max_size() << "\n";
}


void	test_map() {

	test_insert(10);
	test_insert(100);
	test_insert(1000);

	test_size();

}
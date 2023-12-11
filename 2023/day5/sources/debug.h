#include <array>
#include <vector>
#include <iostream>

namespace day5
{

inline void print_map(std::array<long long, 3>* curr_map)
{
	std::cout << "Using map:"
		<< " d" << curr_map->at(0)
		<< " s" << curr_map->at(1)
		<< " r" << curr_map->at(2)
		<< std::endl;
}

inline void print_ids(std::vector<long long>* id_list)
{
	std::cout << "IDs:";

	for (long long id : *id_list) {
		std::cout << " " << id;
		printf(" (%lld) ", id);
	}

	std::cout << std::endl;
}

}
#include "part1solver.h"
#include "parsing.h"
#include "debug.h"

#include <iostream>
#include <vector>
#include <string>

namespace day5
{
using namespace day5;

part_1_solver::part_1_solver() : solver() {};

void part_1_solver::init_seeds(std::string *curr_line)
{
	parse_seed_ids(curr_line, &this->_seed_ids);
	auto& seed_ids = this->_seed_ids;

	this->_seed_range_found.assign(seed_ids.size(), false);
	std::cout << "parsed seeds" << std::endl;
	print_ids(&seed_ids);
}

void part_1_solver::init_map(std::string *curr_line)
{
	auto& seed_ids = this->_seed_ids;
	auto map_name = parse_map_title(curr_line);

	print_ids(&seed_ids);
	std::cout << "                         "
		<< map_name
		<< std::endl;

	this->_seed_range_found.assign(seed_ids.size(), false);
}

void part_1_solver::parse_line(int line_number, std::string *curr_line)
{
	// Parse seeds
	if (line_number == 1) {
		return this->init_seeds(curr_line);
	}

	// Skip empty
	if (curr_line->empty()) {
		return;
	}

	// If this is a map title -> parse, init, return
	// TODO: this isnt very efficient because it searches the entire line
	if (curr_line->rfind(':') != std::string::npos) {
		return this->init_map(curr_line);
	}

	long long new_id;
	long long curr_seed = 0;
	this->_parsed_map = parse_map_line(curr_line);

	for (auto id : this->_seed_ids) {
		if (this->_seed_range_found.at(curr_seed)) {
			curr_seed++;
			continue;
		}

		new_id = translate_to_range(id, &this->_parsed_map);
		if (new_id != id) {
			this->_seed_range_found[curr_seed] = true;
			this->_seed_ids[curr_seed] = new_id;
		}

		curr_seed++;
	}
}

long long part_1_solver::get_result()
{
	print_ids(&this->_seed_ids);
	long long result = INT_MAX;
	for (auto id : this->_seed_ids) {
		if (id < result) result = id;
	}
    return result;
}

}

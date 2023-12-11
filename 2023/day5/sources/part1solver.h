#ifndef DAY5_PART1SOLVER_H
#define DAY5_PART1SOLVER_H

#include <string>
#include <vector>
#include <array>
#include "solver.h"

namespace day5
{

class part_1_solver : public day5::solver<long long>
{

public:
	part_1_solver();

	void parse_line(int line_number, std::string* curr_line) override;
	long long get_result() override;

private:
	std::array<long long, 3> _parsed_map;
	std::vector<long long> _seed_ids{};
	std::vector<bool> _seed_range_found{};

	void init_seeds(std::string* curr_line);
	void init_map(std::string* curr_line);
};

}

#endif DAY5_PART1SOLVER_H

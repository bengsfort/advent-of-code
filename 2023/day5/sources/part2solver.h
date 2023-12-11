#ifndef DAY5_PART2SOLVER_H
#define DAY5_PART2SOLVER_H

#include <string>
#include "solver.h"

namespace day5
{

class part_2_solver : public day5::solver<long long>
{
public:
	part_2_solver();

	void parse_line(int line_number, std::string* curr_line) override;
	long long get_result() override;

};

}

#endif DAY5_PART2SOLVER_H

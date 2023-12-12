#ifndef DAY5_PART2SOLVER_H
#define DAY5_PART2SOLVER_H

#include <string>
#include <vector>
#include <mutex>
#include "solver.h"

namespace day5
{

class part_2_solver : public day5::solver<long long>
{

public:
	part_2_solver();

	void parse_line(int line_number, std::string* curr_line) override;
	long long get_result() override;

private:
	long long _result = LONG_LONG_MAX;
	std::vector<std::array<long long, 3>> _test_maps;
	std::mutex<std::vector<long long>> _pending_results{};
	std::mutex<std::vector<long long>> _curr_range_pending{};
	std::vector<long long> _seed_ranges{};

	void init_seeds(std::string* curr_line);
	void init_map(std::string* curr_line);
	void thread_solve_range(long long start, long long len);
};

}

#endif DAY5_PART2SOLVER_H

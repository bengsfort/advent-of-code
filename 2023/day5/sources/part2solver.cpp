#include "part2solver.h"
#include "parsing.h"
#include "debug.h"

#include <string>

// TODO: impl
/*
 Idea:
 - Get number of threads we can handle
 - divide each seed range by that number
 - spin up threads, pass each one through
 - main thread vector (array?) to store result for each
 - once all are finished, merge them into a single value (lowest wins)
 - Repeat
*/

namespace day5
{
using namespace day5;

part_2_solver::part_2_solver() : solver() {};

void part_2_solver::parse_line(int line_number, std::string *curr_line)
{
	if (line_number == 1) {
		return this->init_seeds(curr_line);
	}

	if (curr_line->empty()) {
		return;
	}

	if (curr_line->rfind(':') != std::string::npos) {
		return this->init_map(curr_line);
	}

	this->_test_maps.push_back(parse_map_line(curr_line));
}

long long part_2_solver::get_result()
{
	// get hardware thread limit
	// split each individual range up by that limit
	// create threads for each -> thread_solve_range
	// results should be in _curr_range_pending
	// get smallest of those, toss into _pending_results (should this just be _pending result?)
	// Keep going until all ranges have been handled
	// profit

    return 0;
}

void part_2_solver::init_seeds(std::string *curr_line)
{
	parse_seed_ids(curr_line, &this->_seed_ranges);
	auto& seed_ids = this->_seed_ranges;

	std::cout << "parsed seeds" << std::endl;
	print_ids(&seed_ids);
}

// these maybe arent needed as much now XD
void part_2_solver::init_map(std::string *curr_line)
{
	auto map_name = parse_map_title(curr_line);
	std::cout << " parsed " << map_name << std::endl;
}


void part_2_solver::thread_solve_range(long long start, long long len)
{
	// do normal pt1 flow, but use _test_maps instead of lines
	// get the smallest 'result' from this range, put in the _pending_results vec
}

}

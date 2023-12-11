#include "part2solver.h"
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

part_2_solver::part_2_solver() : solver()
{
	// todo
};


void part_2_solver::parse_line(int line_number, std::string *curr_line)
{
	// todo
}

long long part_2_solver::get_result()
{
    return 0;
}

}

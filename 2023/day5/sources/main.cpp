#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <utilities.h>

#include "debug.h"
#include "parsing.h"
#include "solver.h"
#include "part1solver.h"
#include "part2solver.h"

using namespace std;

// TODO: Part 2 D:
// Possible solutions:
// - Idea 1
//   - Parse maps first, create range map for lowest-possible result
//   - Create block-list of values that cannot convert into the lowest-possible range
//   - Iterate through provided ranges, discarding any ID's that are in the block list
// - Idea 2
//   - ???????????

// Solving ------------------------------------

long long translate_to_range(long long id, array<long long, 3>* map)
{
	auto& [ dst_start, src_start, len ] = *map;
	if (id >= src_start && id <= (src_start + len)) {
		return dst_start + (id - src_start);
	}
	return id;
}

// https://adventofcode.com/2023/day/5
// ./build/Debug/day4.exe --file=./inputs/test.txt
// ./build/Debug/day4.exe --file=./inputs/codes.txt
//
// Test cases:
// - Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78, humidity 78, location 82.
// - Seed 14, soil 14, fertilizer 53, water 49, light 42, temperature 42, humidity 43, location 43.
// - Seed 55, soil 57, fertilizer 57, water 53, light 46, temperature 82, humidity 82, location 86.
// - Seed 13, soil 13, fertilizer 52, water 41, light 34, temperature 34, humidity 35, location 35.
// - Result: 35 (lowest)
int main(int argc, char* argv[])
{
	fstream file_handle = utilities::get_input_file(argc, argv, "--file");
	bool solve_pt1 = utilities::has_arg(argc, argv, "--pt1");

	day5::solver<long long>* active_solver = nullptr;
	if (solve_pt1) {
		active_solver = new day5::part_1_solver();
	} else {
		active_solver = new day5::part_2_solver();
	}

	// Iterate through each line and store what we find
	string curr_line;
	int line_number = 0;

	while (getline(file_handle, curr_line)) {
		active_solver->parse_line(++line_number, &curr_line);
	}

	long long result = active_solver->get_result();
	cout << "Result: " << result << endl;

	// Cleanup
	file_handle.close();
	return 0;
}

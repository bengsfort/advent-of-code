#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <utilities.h>
#include <math.h>

#include "debug.h"
#include "parsing.h"

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

	// Iterate through each line and store what we find
	string curr_line;
	int line_number = -1;
	long long result = 0;

	vector<long long> seed_ids{};
	vector<bool> seed_range_found{};
	int curr_seed = 0;
	array<long long, 3> active_map;
	string curr_map_name;

	while (getline(file_handle, curr_line)) {
		line_number++;

		// parse seeds into vector
		if (line_number == 0) {
			day5::parse_seed_ids(&curr_line, &seed_ids);
			seed_range_found.assign(seed_ids.size(), false);
			cout << "line " << line_number << " parsed seeds" << endl;
			day5::print_ids(&seed_ids);
			continue;
		}

		// Skip empty lines
		if (curr_line.empty()) {
			continue;
		}

		// if is a map title -> parse, init, and continue
		if (curr_line.rfind(':') != string::npos) {
			day5::print_ids(&seed_ids);
			curr_map_name = day5::parse_map_title(&curr_line);
			seed_range_found.assign(seed_ids.size(), false);
			cout << "                         " << curr_map_name << endl;
			continue;
		}

		long long new_id;
		curr_seed = 0;
		active_map = day5::parse_map_line(&curr_line);

		for (long long id : seed_ids) {
			if (seed_range_found.at(curr_seed) == true) {
				curr_seed++;
				continue;
			}

			new_id = translate_to_range(id, &active_map);
			if (new_id != id) {
				seed_range_found[curr_seed] = true;
				seed_ids[curr_seed] = new_id;
			}

			curr_seed++;
		}
	}

	result = INT_MAX;
	for (long long id : seed_ids) {
		if (id < result)
			result = id;
	}

	day5::print_ids(&seed_ids);
	cout << "Result: " << result << endl;

	// Cleanup
	file_handle.close();
	return 0;
}

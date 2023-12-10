#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <args.h>
#include <math.h>

using namespace std;

void parse_seed_ids(string* curr_line, vector<int>* results)
{
	int cursor = 0;
	string num_substr;
	int num_start = -1;
	int num_length = 0;

	int start = curr_line->find(':') + 1;

	for (int cursor = start; cursor <= curr_line->length(); cursor++) {
		if (cursor == curr_line->length() || (curr_line->at(cursor) == ' ' || curr_line->at(cursor) == '\0') && num_length > 0) {
			num_substr = curr_line->substr((size_t)num_start, (size_t)num_length);
			results->push_back(stoi(num_substr, nullptr, 10));
			num_start = -1;
			num_length = 0;
			continue;
		}

		if (num_start == -1) num_start = cursor;
		num_length += 1;
	}
}

string parse_map_title(string* curr_line)
{
	int cursor = curr_line->length();
	int name_start = 0;
	int name_length = 0;

	for (cursor = curr_line->length(); curr)
}

// Returns the parsed map line.
// [dst_range_start, src_range_start, length]
array<int, 3> parse_map_line(string* curr_line)
{
	array<int, 3> result{};

	int cursor = 0;
	int column = 0;
	string num_substr;
	int num_start = 0;
	int num_length = 0;

	for (auto character : *curr_line) {
		if (character == ' ' || character == '\0') {
			num_substr = curr_line->substr((size_t)num_start, (size_t)num_length);
			result[column] = stoi(num_substr, nullptr, 10);
			column++;
			num_start = ++cursor;
			num_length = 0;
			continue;
		}

		num_length++;
		cursor++;
	}

	return result;
}

bool translate_to_range(int id, array<int, 3>* map)
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
	char* file_name = utilities::getStringArg(argc, argv, "--file");
	if (file_name == NULL) {
		cout << "Must include an input file with --file" << endl;
		return 1;
	}

	fstream file_handle (file_name);

	if (!file_handle.is_open()) {
		cout << "Could not open input" << endl;
		return errno;
	}

	// Iterate through each line and store what we find
	string curr_line;
	int line_number = -1;
	int result = 0;

	vector<int> seed_ids{};
	vector<int[3]> curr_maps;
	string curr_map_name;

	while (getline(file_handle, curr_line)) {
		line_number++;

		// parse seeds into vector
		if (line_number == 0) {
			parse_seed_ids(&curr_line, &seed_ids);
			cout << "line " << line_number << " parsed seeds" << endl;
			continue;
		}

		// Skip empty lines
		if (curr_line.empty()) {
			cout << "line " << line_number << " empty - skipping" << endl;
			continue;
		}

		// if is a map title -> parse, init, and continue
		if (curr_line.rfind(':') != string::npos) {
			cout << "line " << line_number << " map title" << endl;
			cout << curr_line << endl;
			// TODO: parse
			continue;
		}

		// else parse current line -> translate -> test against seeds -> continue

		// cache locations of all map starts so we can jump around
		// for each seed, iterate through maps
		// parse_map_line -> translate_to_range -> if no change, check other maps
		
		
		cout << curr_line << endl;
	}

	cout << "Result: " << result << endl;

	// Cleanup
	file_handle.close();
	return 0;
}

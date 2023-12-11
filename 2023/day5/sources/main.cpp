#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <args.h>
#include <math.h>

using namespace std;

// TODO: Part 2 D:

// Debug ----------------------------

void print_map(array<long long, 3>* curr_map)
{
	cout << "Using map:"
		<< " d" << curr_map->at(0)
		<< " s" << curr_map->at(1)
		<< " r" << curr_map->at(2)
		<< endl;
}

void print_ids(vector<long long>* id_list)
{
	cout << "IDs:";

	for (long long id : *id_list) {
		cout << " " << id;
		printf(" (%lld) ", id);
	}

	cout << endl;
}

// Parsing --------------------------

void parse_seed_ids(string* curr_line, vector<long long>* results)
{
	int cursor = 0;
	string num_substr;
	int num_start = -1;
	int num_length = 0;

	int start = curr_line->find(':') + 1;

	for (int cursor = start; cursor <= curr_line->length(); cursor++) {
		if (cursor == curr_line->length() || (curr_line->at(cursor) == ' ' || curr_line->at(cursor) == '\0') && num_length > 0) {
			num_substr = curr_line->substr((size_t)num_start, (size_t)num_length);
			results->push_back(stoll(num_substr, nullptr, 10));
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

	while (cursor >= 0)
	{
		cursor--;

		if (curr_line->at(cursor) == ':' || curr_line->at(cursor) == ' ') {
			name_start = cursor - 1;
			continue;
		}

		if (curr_line->at(cursor) == '-') {
			return curr_line->substr(cursor + 1, name_start - cursor);
		}
	}

	return curr_line->substr(0, curr_line->length());
}

// Returns the parsed map line.
// [dst_range_start, src_range_start, length]
array<long long, 3> parse_map_line(string* curr_line)
{
	array<long long, 3> result{};

	char character;
	int column = 0;
	string num_substr;
	int num_start = 0;
	int num_length = 0;

	for (int cursor = 0; cursor < curr_line->length(); cursor++) {
		character = curr_line->at(cursor);

		// TODO: there is a more elegant way to do this...
		// but im on remote desktop on my phone so not now
		if (curr_line->length() - 1 == cursor) {
			if (num_length == 0) {
				num_substr = character;
			}
			else {
				num_substr = curr_line->substr((size_t)num_start, (size_t)++num_length);
			}
			result[column] = stoll(num_substr, nullptr, 10);
			break;
		}

		if (character == ' ' || character == '\0') {
			num_substr = curr_line->substr((size_t)num_start, (size_t)num_length);
			result[column] = stoll(num_substr, nullptr, 10);
			column++;
			num_start = cursor + 1;
			num_length = 0;
			continue;
		}

		num_length++;
	}

	return result;
}

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
			parse_seed_ids(&curr_line, &seed_ids);
			seed_range_found.assign(seed_ids.size(), false);
			cout << "line " << line_number << " parsed seeds" << endl;
			print_ids(&seed_ids);
			continue;
		}

		// Skip empty lines
		if (curr_line.empty()) {
			continue;
		}

		// if is a map title -> parse, init, and continue
		if (curr_line.rfind(':') != string::npos) {
			print_ids(&seed_ids);
			curr_map_name = parse_map_title(&curr_line);
			seed_range_found.assign(seed_ids.size(), false);
			cout << "                         " << curr_map_name << endl;
			continue;
		}

		long long new_id;
		curr_seed = 0;
		active_map = parse_map_line(&curr_line);

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

	print_ids(&seed_ids);
	cout << "Result: " << result << endl;

	// Cleanup
	file_handle.close();
	return 0;
}

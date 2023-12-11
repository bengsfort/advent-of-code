#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utilities.h>


using namespace std;

struct SchematicEntry
{
	int x;
	int y;
	char str;
};

struct SchematicNumber
{
	int x;
	int y;
	string num;
};


int clamp(int val, int min, int max)
{
	if (val < min) {
		return min;
	} else if (val > max) {
		return max;
	}
	return val;
}

char get_schematic_symbol(char val, bool gears_only)
{
	// Handle gears separately
	if (gears_only == true) {
		return val == '*' ? val : 0;
	}

	// Ignore digits, whitespace, and periods.
	if (isdigit(val) != 0 || val == ' ' || val == '.') {
		return 0;
	}

	return val;
}

string get_number_group(int start, string in)
{
	string result;

	if (isdigit(in[start]) == 0) {
		return result;
	}

	int cursor;

	// Iterate until we run out of digit characters so we can calculate
	// the start and end point of the digits
	for (cursor = start; cursor < in.length(); cursor++) {
		if (isdigit(in[cursor]) == 0) {
			break;
		}

		result.push_back(in[cursor]);
	}

	return result;
}

bool is_adjacent(SchematicEntry* sym, SchematicNumber* number)
{
	int y_diff = abs(number->y - sym->y);
	if (y_diff > 1) {
		return false;
	}

	int x_start = number->x;
	int x_end = number->x + number->num.length() - 1;

	if (abs(x_start - sym->x) <= 1 || abs(x_end - sym->x) <= 1) {
		return true;
	}

	return false;
}

int solve_adjacent(vector<SchematicEntry>* entries, vector<vector<SchematicNumber>>* numbers)
{
	int result = 0;
	int row_start, row_end, row = 0;

	for (SchematicEntry entry : *entries) {
		row_start = max(entry.y - 1, 0);
		row_end = min(entry.y + 1, (int)numbers->size());

		for (row = row_start; row <= row_end; row++) {
			for (SchematicNumber number : numbers->at(row)) {
				if (is_adjacent(&entry, &number)) {
					result += stoi(number.num, nullptr, 10);
				}
			}
		}
	}

	return result;
}

int solve_gears(vector<SchematicEntry>* entries, vector<vector<SchematicNumber>>* numbers)
{
	int result = 0;
	int nums_found = 0;
	int gear_ratio = 1;
	int row_start, row_end, row = 0;

	for (SchematicEntry entry : *entries) {
		nums_found = 0;
		gear_ratio = 1;
		row_start = max(entry.y - 1, 0);
		row_end = min(entry.y + 1, (int)numbers->size());

		for (row = row_start; row <= row_end; row++) {
			for (SchematicNumber number : numbers->at(row)) {
				if (is_adjacent(&entry, &number)) {
					gear_ratio *= stoi(number.num, nullptr, 10);
					nums_found++;
				}
			}
		}

		if (gear_ratio > 1 && nums_found == 2) {
			result += gear_ratio;
		}
	}

	return result;
}

// https://adventofcode.com/2023/day/3
// ./build/Debug/day3.exe --file=./inputs/test.txt
// TODO: this is a horribly inefficient solution as we generate a million
// damn strings all over the place, namely whenever we parse the numbers.
// it would be much better to store ptr's to the numbers in the file buffer,
// along with length, and then use those instead.
int main(int argc, char* argv[])
{
	fstream file_handle = utilities::get_input_file(argc, argv, "--file");
	bool gears_only = utilities::has_arg(argc, argv, "--gears");

	int col_count, row_count = 0;
	string number_group;

	vector<vector<SchematicNumber>> schematic_number_map;
	vector<SchematicNumber> schematic_numbers_row;
	vector<SchematicEntry> schematic_entries;

	// Iterate through each line and store what we find
	string curr_line;
	while (getline(file_handle, curr_line)) {
		col_count = 0;
		schematic_numbers_row = vector<SchematicNumber>();

		// Iterate through the chars of a line to capture any numbers or symbols
		while (col_count < curr_line.size()) {
			number_group = get_number_group(col_count, curr_line);

			// Handle numbers
			if (!number_group.empty()) {
				schematic_numbers_row.push_back({
					col_count,
					row_count,
					number_group
				});
				col_count += number_group.length();
				continue;
			}

			// Handle symbols
			if (get_schematic_symbol(curr_line[col_count], gears_only) != 0) {
				schematic_entries.push_back({
					col_count,
					row_count,
					curr_line[col_count]
				});
			}

			col_count++;
		}

		schematic_number_map.push_back(schematic_numbers_row);
		row_count++;
		printf("Line: %s\n", curr_line.c_str());
	}

	// Solve. Find adjacents
	int result = gears_only == true
		? solve_gears(&schematic_entries, &schematic_number_map)
		: solve_adjacent(&schematic_entries, &schematic_number_map);
	printf("Result: %d\n", result);

	// Cleanup
	file_handle.close();
	return 0;
}

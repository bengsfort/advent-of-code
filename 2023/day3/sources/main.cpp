#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <args.h>
#include <math.h>


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

/*
string get_state(SchematicEntry* entry)
{
	string str;

	str.push_back(entry->str);
	str.append(" {");
	str.append(to_string(entry->x).c_str());
	str.push_back(',');
	str.append(to_string(entry->y).c_str());
	str.push_back('}');

	return str;
}

string get_state(SchematicNumber* number)
{
	string str(number->num);

	str.append(" {");
	str.append(to_string(number->x).c_str());
	str.push_back(',');
	str.append(to_string(number->y).c_str());
	str.push_back('}');

	return str;
}
*/

int clamp(int val, int min, int max)
{
	if (val < min) {
		return min;
	} else if (val > max) {
		return max;
	}
	return val;
}

char get_schematic_symbol(char val)
{
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
	//printf("Checking %s: %s ", get_state(sym).c_str(), get_state(number).c_str());
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

// https://adventofcode.com/2023/day/3
// ./build/Debug/day3.exe --file=./inputs/test.txt
// TODO: this is a horribly inefficient solution as we generate a million
// damn strings all over the place. it would be much better to store ptr's
// to the numbers in the file buffer, along with length, and then use those
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

	int result = 0;
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
			if (get_schematic_symbol(curr_line[col_count]) != 0) {
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

	/*
	// Print entries
	printf("Entries:\n");
	for (SchematicEntry entry : schematic_entries) {
		printf("\t{ x: %d, y: %d, char: %c }\n", entry.x, entry.y, entry.str);
	}

	// Print numbers
	printf("Numbers:\n");
	for (vector<SchematicNumber> row : schematic_number_map) {
		for (SchematicNumber num : row) {
			printf("\t{ x: %d, y: %d, num: %s }\n", num.x, num.y, num.num.c_str());
		}
	}
	*/

	// Solve. Find adjacents
	int row_start, row_end, row = 0;
	for (SchematicEntry entry : schematic_entries) {
		row_start = max(entry.y - 1, 0);
		row_end = min(entry.y + 1, (int)schematic_number_map.size());

		for (row = row_start; row <= row_end; row++) {
			for (SchematicNumber number : schematic_number_map[row]) {
				if (is_adjacent(&entry, &number)) {
					result += stoi(number.num, nullptr, 10);
				}
			}
		}
	}
	printf("Result: %d\n", result);

	// Cleanup
	file_handle.close();
	return 0;
}

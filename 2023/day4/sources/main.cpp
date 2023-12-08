#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <args.h>
#include <math.h>

using namespace std;

// https://adventofcode.com/2023/day/4 
// ./build/Debug/day4.exe --file=./inputs/test.txt
// ./build/Debug/day4.exe --file=./inputs/codes.txt
//
// Test cases:
// - Result: 13
// - Card 1: 8pts
// - Cards 2,3: 2pts each
// - Card 4: 1pt
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
	int result = 0;

	map<string, int> copy_map;
	vector<string> winning_numbers;
	string entry;
	int cursor, seperator_index, card_total;
	int num_start;

	while (getline(file_handle, curr_line)) {
		// Reset
		cursor = 0;
		seperator_index = 0;
		card_total = 0;
		num_start = -1;
		entry.clear();
		winning_numbers.clear();

		// TODO: Parse & solve.
		cout << curr_line << endl;

		// Start after the card definition.
		seperator_index = curr_line.find('|');
		cursor = curr_line.find(':');

		// TODO: Create a better iterator, this is a bit wonky

		// Parsing winning numbers.
		for (cursor += 1; cursor < seperator_index; cursor++) {
			// If we are checking a digit, just heckin keep going
			if (curr_line[cursor] != ' ') {
				if (num_start == -1) num_start = cursor;
				continue;
			}

			if (num_start == -1) {
				continue;
			}

			// If we are at the boundary; store things
			winning_numbers.push_back(
				curr_line.substr((size_t)num_start, (size_t)(cursor - num_start))
			);
			num_start = -1;
		}

		// Parse our numbers and simultaneously look for winners.
		num_start = -1;
		for (cursor = seperator_index + 1; cursor <= curr_line.length(); cursor++) {
			// If we are checking a digit, just heckin keep going
			if (curr_line[cursor] != ' ' && curr_line[cursor] != '\0') {
				if (num_start == -1) num_start = cursor;
				continue;
			}

			if (num_start == -1) {
				continue;
			}

			// We are at a boundary; check for the number
			// 
			// NOTE: we could maybe use .find() to "simplify" this, 
			// but I don't think it actually would simplify it much.
			entry = curr_line.substr(num_start, (size_t)(cursor - num_start));
			for (string winning : winning_numbers) {
				if (winning != entry) {
					continue;
				}

				card_total = card_total == 0 ? 1 : card_total * 2;
				printf("%s matches %s! Adding to card total %d\n", entry.c_str(), winning.c_str(), card_total);
				break;
			}
			num_start = -1;
		}

		result += card_total;
		printf("Points: %d\n", card_total);
	}


	printf("Result: %d\n", result);

	// Cleanup
	file_handle.close();
	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <args.h>
#include <math.h>

using namespace std;

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
	int result = 0;

	while (getline(file_handle, curr_line)) {
		// Reset
		// TODO: Parse & solve.
		cout << curr_line << endl;
	}

	cout << "Result: %d" << result << endl;

	// Cleanup
	file_handle.close();
	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
	while (getline(file_handle, curr_line)) {
		// TODO: Parse.
		cout << curr_line << endl;
	}

	// TODO: Solve.

	// Cleanup
	file_handle.close();
	return 0;
}

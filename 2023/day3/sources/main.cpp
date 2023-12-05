#include <iostream>
#include <fstream>
#include <args.h>

using namespace std;

// https://adventofcode.com/2023/day/3
int main(int argc, char* argv[])
{
	char* file_name = utilities::getStringArg(argc, argv, "--file");
	if (file_name == NULL) {
		cout << "Must include an input file with --file" << endl;
		return 1;
	}

    string curr_line;
	fstream file_handle (file_name);

	if (!file_handle.is_open()) {
		cout << "Could not open input" << endl;
		return errno;
	}

	int result = 0;

	while (getline(file_handle, curr_line)) {
		printf("Line: %s\n", curr_line.c_str());
	}

	printf("Result: %d", result);

	// Cleanup
	file_handle.close();
	return 0;
}
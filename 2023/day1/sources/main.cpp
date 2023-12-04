#include <iostream>
#include <fstream>
#include <args.h>

using namespace std;

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
	char line_code[3] = {0, 0, 0};

	while (getline(file_handle, curr_line)) {
		line_code[0] = 0;
		line_code[1] = 0;

		// Iterate through line and find the first and last integers
		for (char c : curr_line) {
			if (isdigit(c) == 0) {
				continue;
			}

			if (line_code[0] == 0) {
				line_code[0] = c;
			}
			line_code[1] = c;
		}

		cout << "line " << curr_line << " found " << line_code << endl;
		result += strtol(line_code, nullptr, 10);
	}

	cout << "Result is: " << result << endl;

	// Cleanup
	file_handle.close();
	return 0;
}

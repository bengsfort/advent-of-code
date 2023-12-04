#include <iostream>
#include <fstream>
#include <args.h>

using namespace std;

const char * written_numbers[] = {
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
};

const char number_values[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

char parseWrittenNumber(string str, int start)
{
	char start_char = str[start];
	int count = 0;
	size_t num_length = 0;
	string substr;

	for (const char * number : written_numbers) {
		num_length = strlen(number);

		// If the start char doesn't equal a number, OR counting that full
		// number would push us over the string length, move on to the next
		if (start_char != number[0] || start + num_length > str.length()) {
			count++;
			continue;
		}

		substr = str.substr(start, num_length);
		if (substr == number) {
			return number_values[count];
		}

		count++;
	}

	return 0;
}

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
	char found_num;
	int line_pos;

	while (getline(file_handle, curr_line)) {
		// Reset
		line_code[0] = 0;
		line_code[1] = 0;
		line_pos = 0;
		found_num = 0;

		// Iterate through line and find the first and last integers
		for (char c : curr_line) {
			if (isdigit(c) != 0) {
				found_num = c;
			} else {
				found_num = parseWrittenNumber(curr_line, line_pos);
			}


			if (found_num == 0) {
				line_pos++;
				continue;
			}

			if (line_code[0] == 0) {
				line_code[0] = found_num;
			}

			line_code[1] = found_num;
			line_pos++;
		}

		cout << "line " << curr_line << " found " << line_code << endl;
		result += strtol(line_code, nullptr, 10);
	}

	cout << "Result is: " << result << endl;

	// Cleanup
	file_handle.close();
	return 0;
}

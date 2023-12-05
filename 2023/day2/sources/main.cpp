#include <iostream>
#include <fstream>
#include <args.h>

using namespace std;

const char * colors[] = { "red", "green", "blue" };
const size_t color_lens[] = {
	strlen(colors[0]),
	strlen(colors[1]),
	strlen(colors[2])
};

// Just part 1 things
// const int red_cube_max = 12;
// const int green_cube_max = 13;
// const int blue_cube_max = 14;


void parseGame(string game_str, array<int, 3>* rgb)
{
	// reset array
	rgb->fill(0);
	string curr_num;
	int curr_num_val;

	int color_idx;
	size_t color_len;
	size_t cursor = game_str.find_first_of(':') + 1;

	while (cursor < game_str.length()) {
		// Skip non-alphanumerics
		if (game_str[cursor] == ' ' || game_str[cursor] == ',' || game_str[cursor] == ';') {
			cursor++;
			continue;
		}

		// Append digits together
		if (isdigit(game_str[cursor])) {
			curr_num += game_str[cursor];
			cursor++;
			continue;
		}

		// determine which color it is
		color_idx = 0;

		for (const char * color : colors) {
			color_len = color_lens[color_idx];

			// If the first characters don't match, move on
			if (color[0] != game_str[cursor]) {
				color_idx++;
				continue;
			}

			curr_num_val = stoi(curr_num, nullptr, 10);

			// Store the new var IF it is greater than the last
			if (rgb->at(color_idx) < curr_num_val) {
				rgb->at(color_idx) = curr_num_val;
			}

			curr_num.clear();
			cursor += color_len;
			break;
		}
	}
}

// https://adventofcode.com/2023/day/2
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

	array<int, 3> rgb;
	int game_num = 0;
	int result = 0;

	while (getline(file_handle, curr_line)) {
		game_num++;

		parseGame(curr_line, &rgb);
		printf("Line %d: found r%d, g%d, b%d\n", game_num, rgb[0], rgb[1], rgb[2]);

		// Part 1 things
		// if (rgb[0] > red_cube_max || rgb[1] > green_cube_max || rgb[2] > blue_cube_max) {
		// 	printf(" !! INVALID\n");
		// 	continue;
		// }
		// result += game_num;

		result += rgb[0] * rgb[1] * rgb[2];
	}

	printf("Result: %d", result);

	// Cleanup
	file_handle.close();
	return 0;
}

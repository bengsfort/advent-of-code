#include "parsing.h"

#include <string>
#include <vector>
#include <array>

void day5::parse_seed_ids(std::string* curr_line, std::vector<long long>* results)
{
	int cursor = 0;
	std::string num_substr;
	int num_start = -1;
	int num_length = 0;

	int start = curr_line->find(':') + 1;

	for (int cursor = start; cursor <= curr_line->length(); cursor++) {
		if (cursor == curr_line->length() || (curr_line->at(cursor) == ' ' || curr_line->at(cursor) == '\0') && num_length > 0) {
			num_substr = curr_line->substr((size_t)num_start, (size_t)num_length);
			results->push_back(std::stoll(num_substr, nullptr, 10));
			num_start = -1;
			num_length = 0;
			continue;
		}

		if (num_start == -1) num_start = cursor;
		num_length += 1;
	}
}

std::string day5::parse_map_title(std::string* curr_line)
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
std::array<long long, 3> day5::parse_map_line(std::string* curr_line)
{
	std::array<long long, 3> result{};
	std::string num_substr;

	char character;
	int column = 0;
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
			result[column] = std::stoll(num_substr, nullptr, 10);
			break;
		}

		if (character == ' ' || character == '\0') {
			num_substr = curr_line->substr((size_t)num_start, (size_t)num_length);
			result[column] = std::stoll(num_substr, nullptr, 10);
			column++;
			num_start = cursor + 1;
			num_length = 0;
			continue;
		}

		num_length++;
	}

	return result;
}
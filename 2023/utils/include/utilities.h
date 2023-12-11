#include <iostream>

namespace utilities
{
	bool has_arg(int argc, char* argv[], char const* arg_name);
	char* get_string_arg(int argc, char* argv[], char const* arg_name);
	std::fstream get_input_file(int argc, char* argv[], char const* arg_name);
}

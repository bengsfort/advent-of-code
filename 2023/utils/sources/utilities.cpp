#include <cstring>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "utilities.h"

bool utilities::has_arg(int argc, char *argv[], char const* arg_name)
{
	// Can't be there if there are no args
	if (argc <= 1) {
		return false;
	}

	int index;
	for (index = 1; index < argc; index++) {
		if (strcmp(argv[index], arg_name) == 0) {
			return true;
		}
	}

    return false;
}

// TODO: this does not currently handle if the string is wrapped in "" or ''
// ie: --file=./inputs/codes.txt works but --file="./inputs/codes.txt" does not
char* utilities::get_string_arg(int argc, char *argv[], const char* arg_name)
{
	// Can't be there if there are no args...
	if (argc <= 1) {
		return NULL;
	}

	char* arg;

	// Find the arg within the array
	int index;
	for (index = 1; index < argc; index++) {
		arg = strstr(argv[index], arg_name);
		if (arg != NULL) {
			break;
		}
	}

	if (arg == NULL) {
		return NULL;
	}

	// Parse the actual value from the arg
	arg = strstr(arg, "=");
	if (arg == NULL) {
		return NULL;
	}

    return arg + 1;
}

// Opens and returns the file provided by the given arg_name param.
// Throws if there is an error accessing or opening the file.
std::fstream utilities::get_input_file(int argc, char* argv[], char const* arg_name)
{
	char* file_name = utilities::get_string_arg(argc, argv, arg_name);
	if (file_name == NULL) {
		std::cout << "Must include an input file with " << arg_name << std::endl;
		throw std::runtime_error("no input file");
	}

	std::fstream file_handle (file_name);
	if (!file_handle.is_open()) {
		throw std::runtime_error("file not open");
	}

	return file_handle;
}

#include <cstring>
#include <iostream>
#include <filesystem>
#include "args.h"

using std::string;

bool utilities::hasArg(int argc, char *argv[], char const* argName)
{
	// Can't be there if there are no args
	if (argc <= 1) {
		return false;
	}

	int index;
	for (index = 1; index < argc; index++) {
		if (strcmp(argv[index], argName) == 0) {
			return true;
		}
	}

    return false;
}

// TODO: this does not currently handle if the string is wrapped in "" or ''
// ie: --file=./inputs/codes.txt works but --file="./inputs/codes.txt" does not
char* utilities::getStringArg(int argc, char *argv[], const char* argName)
{
	// Can't be there if there are no args...
	if (argc <= 1) {
		return NULL;
	}

	char* arg;

	// Find the arg within the array
	int index;
	for (index = 1; index < argc; index++) {
		arg = strstr(argv[index], argName);
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

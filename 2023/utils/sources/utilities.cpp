#include <string>
#include <iostream>
#include "utilities/args.h"

using std::string;

bool utilities::hasArg(int argc, char *argv[], char const* argName)
{
	// Can't be there if there are no args
	if (argc <= 1) {
		return false;
	}

	std::cout << "Checking args" << std::endl;
	char* arg;
	int index;
	for (index = 1; index < argc; index++) {
		arg = argv[index];
		std::cout << arg << std::endl;
	}

    return false;
}

string utilities::getStringArg(int argc, char *argv[], const char* argName)
{
    return string();
}

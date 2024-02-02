#include "error.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

static bool is_valid_argc(const int argc) {
	return argc == 4;
}

int main(int argc, char *argv[]) {
	if (!is_valid_argc(argc)) {
		put_error(ERR_INVALID_ARGS);
		return EXIT_FAILURE;
	}

	std::string filename = argv[1];
	std::string s1       = argv[2];
	std::string s2       = argv[3];
	std::cout << filename << " " << s1 << " " << s2 << std::endl;

	return EXIT_SUCCESS;
}

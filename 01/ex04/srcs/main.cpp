#include "color.hpp"
#include "error.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

static bool is_valid_argc(const int argc) {
	return argc == 4;
}

static void put_error(const std::string &message) {
	std::cerr << COLOR_RED << "Error: " << message << COLOR_END << std::endl;
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

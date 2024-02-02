#include "error.hpp"
#include "file.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

static bool is_valid_argc(const int argc) {
	return argc == 4;
}

static bool create_replaced_file(
	const std::string &filename, const std::string &s1, const std::string &s2
) {
	File file(filename, s1, s2);

	return file.create_replaced_file();
}

int main(int argc, const char *argv[]) {
	if (!is_valid_argc(argc)) {
		put_error(ERR_INVALID_ARGS);
		return EXIT_FAILURE;
	}

	// todo: handle error
	const std::string filename = argv[1];
	const std::string s1       = argv[2];
	const std::string s2       = argv[3];
	std::cout << filename << " " << s1 << " " << s2 << std::endl;

	if (!create_replaced_file(filename, s1, s2)) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

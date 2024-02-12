#include "error.hpp"
#include "file_replace.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

static bool is_valid_argc(const int argc) {
	return argc == 4;
}

static void put_guide() {
	static const std::string message =
		"./sed [filename] [src: before] [replaced: after]";
	std::cerr << message << std::endl;
}

static bool is_valid_string(const std::string &filename, const std::string &src) {
	return !(filename.empty() || src.empty());
}

static void create_replaced_file(
	const std::string &filename, const std::string &src, const std::string &replaced
) {
	FileReplace file_replace(filename, src, replaced);

	file_replace.create_replaced_file();
}

int main(int argc, const char *argv[]) {
	if (!is_valid_argc(argc)) {
		put_error(ERR_INVALID_ARGS);
		put_guide();
		return EXIT_FAILURE;
	}

	const std::string filename = argv[1];
	const std::string src      = argv[2];
	const std::string replaced = argv[3];
	if (!is_valid_string(filename, src)) {
		put_error(ERR_INVALID_ARGS);
		return EXIT_FAILURE;
	}

	create_replaced_file(filename, src, replaced);
	return EXIT_SUCCESS;
}

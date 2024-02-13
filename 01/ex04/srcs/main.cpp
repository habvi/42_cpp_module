#include "error.hpp"
#include "file_replace.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

static bool IsValidArgc(const int argc) {
	return argc == 4;
}

static void PutUsage() {
	static const std::string kMessage =
		"    ./sed [filename] [src: before] [replaced: after]";
	std::cerr << "Usage:\n" << kMessage << std::endl;
}

static bool IsValidString(const std::string &filename, const std::string &src) {
	return !(filename.empty() || src.empty());
}

static void CreateReplacedFile(
	const std::string &filename, const std::string &src, const std::string &replaced
) {
	FileReplace file_replace(filename, src, replaced);

	const bool result = file_replace.CreateReplacedFile();
	if (!result) {
		PutError(ERR_REPLACE);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, const char *argv[]) {
	if (!IsValidArgc(argc)) {
		PutError(ERR_INVALID_ARGS);
		PutUsage();
		return EXIT_FAILURE;
	}

	const std::string filename = argv[1];
	const std::string src      = argv[2];
	const std::string replaced = argv[3];
	if (!IsValidString(filename, src)) {
		PutError(ERR_INVALID_ARGS);
		return EXIT_FAILURE;
	}

	CreateReplacedFile(filename, src, replaced);
	return EXIT_SUCCESS;
}

#include "Harl.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

static void PutErrorArgs() {
	static const std::string kMessage = "invalid arguments";
	std::cerr << COLOR_RED << "Error: " << kMessage << COLOR_END << std::endl;
}

static void PutUsage() {
	static const std::string kMessage =
		"    ./harlFilter [ DEBUG, INFO, WARNING, or ERROR ]";
	std::cerr << "Usage:\n" << kMessage << std::endl;
}

static bool IsValidArgs(const int argc) {
	return argc == 2;
}

int main(int argc, const char *argv[]) {
	if (!IsValidArgs(argc)) {
		PutErrorArgs();
		PutUsage();
		return EXIT_FAILURE;
	}

	Harl              harl;
	const std::string level = argv[1];

	harl.Filter(level);

	return EXIT_SUCCESS;
}

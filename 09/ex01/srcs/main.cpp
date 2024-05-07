#include "RPN.hpp"
#include "color.hpp"
#include <cstdlib>
#include <iostream>

namespace {
	void PrintError(const std::string &message) {
		std::cout << COLOR_RED << message << COLOR_END << std::endl;
	}
} // namespace

int main(int argc, char **argv) {
	if (argc != 2) {
		PrintError("Error: invalid argument");
		return EXIT_FAILURE;
	}

	const std::string rpn_str(argv[1]);
	try {
		const int result_num = RPN::Calcurate(rpn_str);
		std::cout << result_num << std::endl;
	} catch (const std::exception &e) {
		PrintError("Error");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

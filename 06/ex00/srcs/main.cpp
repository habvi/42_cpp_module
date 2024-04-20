#include "ScalarConverter.hpp"
#include <cstdlib>
#include <iostream>

static void RunOriginalTest() {}

static void RunLikeSubject(const std::string &str) {
	ScalarConverter::convert(str);
}

int main(int argc, const char **argv) {
	if (argc == 1) {
		RunOriginalTest();
	} else if (argc == 2) {
		RunLikeSubject(std::string(argv[1]));
	} else {
		std::cerr << "Usage:\n"
				  << "  [subject] ./convert <argument>\n"
				  << "  [test]    ./convert" << std::endl;
	}
	return EXIT_SUCCESS;
}

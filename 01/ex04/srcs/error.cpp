#include "color.hpp"
#include <iostream>
#include <string>

void put_error(const std::string &message) {
	std::cerr << COLOR_RED << "Error: " << message << COLOR_END << std::endl;
}

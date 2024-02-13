#include "color.hpp"
#include <iostream>
#include <string>

void PutError(const std::string &message) {
	std::cerr << COLOR_RED << "Error: " << message << COLOR_END << std::endl;
}

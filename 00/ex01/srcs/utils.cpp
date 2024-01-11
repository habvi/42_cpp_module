#include "utils.hpp"
#include <iomanip>
#include <iostream>
#include <limits>

void input_left_align(const std::string &title, std::string &dst, const int width) {
	std::cout << std::setw(width) << std::left << title << ": ";
	std::cin >> dst;
}

t_result
input_left_align(const std::string &title, unsigned int &dst, const int width) {
	std::cout << std::setw(width) << std::left << title << ": ";
	std::cin >> dst;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return FAILURE;
	}
	return SUCCESS;
}

void output_left_align(
	const std::string &title, const std::string &s, const int width
) {
	std::cout << std::setw(width) << std::left << title << ": " << s << std::endl;
}

#include "utils.hpp"
#include <iomanip>
#include <iostream>

void input_left_align(const std::string &title, std::string &dst, const int width) {
	std::cout << std::setw(width) << std::left << title << ": ";
	std::cin >> dst;
}

void input_left_align(const std::string &title, unsigned int &dst, const int width) {
	std::cout << std::setw(width) << std::left << title << ": ";
	std::cin >> dst;
}

void output_left_align(
	const std::string &title, const std::string &s, const int width
) {
	std::cout << std::setw(width) << std::left << title << ": " << s << std::endl;
}

#include "io.hpp"
#include "color.hpp"
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

t_result input_line(std::string &dst) {
	if (!std::getline(std::cin, dst)) {
		std::cout << std::endl;
		return EOF;
	}
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return FAILURE;
	}
	return SUCCESS;
}

// true  : Successfully converted to an integer within the valid range.
// false : Not a number at all (e.g. "123a", "\n").
static bool convert_to_integer(const std::string &dst, int &num) {
	std::istringstream iss(dst);

	iss >> num;
	return (iss && iss.eof());
}

// input string -> string &dst
t_result
input_left_align(const std::string &title, std::string &dst, const int width) {
	std::cout << std::setw(width) << std::left << title << ": ";
	return (input_line(dst));
}

// input string -> int &dst
t_result input_left_align(const std::string &title, int &dst, const int width) {
	std::cout << std::setw(width) << std::left << GREEN + title << ": " END;

	std::string tmp_dst;
	t_result    result = input_line(tmp_dst);

	if (result == EOF || result == FAILURE) {
		return result;
	}
	if (!convert_to_integer(tmp_dst, dst)) {
		return FAILURE;
	}
	return SUCCESS;
}

void output_left_align(
	const std::string &title, const std::string &s, const int width
) {
	std::cout << std::setw(width) << std::left << title << ": " << s << std::endl;
}

void put_error(const std::string &message) {
	std::cerr << RED << message << END << std::endl;
}

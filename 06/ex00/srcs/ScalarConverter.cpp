#include "ScalarConverter.hpp"
#include <iostream>

std::string           ScalarConverter::src_;
ScalarConverter::Type ScalarConverter::type_;

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &c) {
	(void)c;
}

const ScalarConverter &ScalarConverter::operator=(const ScalarConverter &c) {
	(void)c;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string &str) {
	src_ = str;
	std::cout << src_ << std::endl;
}

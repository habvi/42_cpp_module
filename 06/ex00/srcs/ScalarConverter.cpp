#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &c) {
	(void)c;
}

const ScalarConverter &ScalarConverter::operator=(const ScalarConverter &c) {
	(void)c;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

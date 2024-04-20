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

bool ScalarConverter::IsTypeChar() {
	return false;
}

bool ScalarConverter::IsTypeInteger() {
	return true;
}

bool ScalarConverter::IsTypeFloat() {
	return false;
}

bool ScalarConverter::IsTypeDouble() {
	return false;
}

void ScalarConverter::SetType() {
	if (IsTypeChar()) {
		type_ = kTypeChar;
	} else if (IsTypeInteger()) {
		type_ = kTypeInt;
	} else if (IsTypeFloat()) {
		type_ = kTypeFloat;
	} else if (IsTypeDouble()) {
		type_ = kTypeDouble;
	} else {
		type_ = kTypeInvalid;
	}
}

void ScalarConverter::convert(const std::string &str) {
	src_ = str;
	SetType();
	std::cout << src_ << " " << type_ << std::endl;
}

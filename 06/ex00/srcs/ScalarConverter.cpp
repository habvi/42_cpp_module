#include "ScalarConverter.hpp"
#include "color.hpp"
#include <cstdlib> // strtod
#include <iostream>

const std::string     ScalarConverter::kMessageImpossible = "impossible";
std::string           ScalarConverter::src_;
ScalarConverter::Type ScalarConverter::type_;
std::ostringstream    ScalarConverter::oss_;

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &c) {
	(void)c;
}

const ScalarConverter &ScalarConverter::operator=(const ScalarConverter &c) {
	(void)c;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

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

void ScalarConverter::SetImpossible() {
	oss_ << COLOR_PINK << kMessageImpossible << COLOR_END << std::endl;
}

template <typename T>
void ScalarConverter::SetConvertEachType(const Type convert_to, const T &scalar) {
	oss_ << convert_to << " " << scalar << std::endl;
}

template <typename T>
void ScalarConverter::Display(
	const std::string &title, const Type convert_to, const T scalar
) {
	oss_ << title << ": ";

	if (type_ == kTypeInvalid) {
		SetImpossible();
	} else {
		SetConvertEachType(convert_to, scalar);
	}
	std::cout << oss_.str();
	oss_.str("");
}

template <typename T>
void ScalarConverter::DisplayConvertAll(const T scalar) {
	static const std::pair<const std::string, const Type> types[] = {
		std::make_pair("char", kTypeChar),
		std::make_pair("int", kTypeInt),
		std::make_pair("float", kTypeFloat),
		std::make_pair("double", kTypeDouble)
	};
	const unsigned int size = sizeof(types) / sizeof(*types);

	for (unsigned int i = 0; i < size; i++) {
		Display(types[i].first, types[i].second, scalar);
	}
}

char ScalarConverter::ConvertToChar() {
	return static_cast<char>(src_[1]);
}

int ScalarConverter::ConvertToInteger() {
	return static_cast<int>(std::atoi(src_.c_str()));
}

float ScalarConverter::ConvertToFloat() {
	std::string except_tail_f = src_.substr(0, src_.size() - 1);
	src_                      = except_tail_f;
	return static_cast<float>(std::strtod(src_.c_str(), NULL));
}

double ScalarConverter::ConvertToDouble() {
	return static_cast<double>(std::strtod(src_.c_str(), NULL));
}

void ScalarConverter::convert(const std::string &str) {
	src_ = str;
	SetType();

	switch (type_) {
	case kTypeChar:
		DisplayConvertAll(ConvertToChar());
		break;
	case kTypeInt:
		DisplayConvertAll(ConvertToInteger());
		break;
	case kTypeFloat:
		DisplayConvertAll(ConvertToFloat());
		break;
	case kTypeDouble:
		DisplayConvertAll(ConvertToDouble());
		break;
	case kTypeInvalid:
		DisplayConvertAll(0);
		break;
	default:
		break;
	}
}

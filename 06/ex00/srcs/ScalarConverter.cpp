#include "ScalarConverter.hpp"
#include "color.hpp"
#include <cstdlib> // strtod
#include <iostream>

const std::string     ScalarConverter::kMessageImpossible     = "impossible";
const std::string     ScalarConverter::kMessageNonDisplayable = "Non displayable";
std::string           ScalarConverter::src_;
ScalarConverter::Type ScalarConverter::type_;
std::ostringstream    ScalarConverter::oss_;

// ----------------------------------------------------------------------------
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &c) {
	(void)c;
}

const ScalarConverter &ScalarConverter::operator=(const ScalarConverter &c) {
	(void)c;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

// ----------------------------------------------------------------------------
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

// ----------------------------------------------------------------------------
void ScalarConverter::SetImpossible() {
	oss_ << COLOR_PINK << kMessageImpossible << COLOR_END << std::endl;
}

template <typename T>
void ScalarConverter::SetConvertEachType(const Type convert_to, const T &scalar) {
	switch (convert_to) {
	case kTypeChar:
		SetConvertToChar(scalar);
		break;
	case kTypeInt:
		SetConvertToInteger(scalar);
		break;
	case kTypeFloat:
		SetConvertToFloat(scalar);
		break;
	case kTypeDouble:
		SetConvertToDouble(scalar);
		break;
	default:
		break;
	}
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

// ----------------------------------------------------------------------------
static char ConvertToChar(const std::string &str) {
	return static_cast<char>(str[1]);
}

static int ConvertToInteger(const std::string &str) {
	return static_cast<int>(std::atoi(str.c_str()));
}

static float ConvertToFloat(const std::string &str) {
	std::string except_tail_f = str.substr(0, str.size() - 1);
	return static_cast<float>(std::strtod(except_tail_f.c_str(), NULL));
}

static double ConvertToDouble(const std::string &str) {
	return static_cast<double>(std::strtod(str.c_str(), NULL));
}

void ScalarConverter::convert(const std::string &str) {
	src_ = str;
	SetType();

	switch (type_) {
	case kTypeChar:
		DisplayConvertAll(ConvertToChar(src_));
		break;
	case kTypeInt:
		DisplayConvertAll(ConvertToInteger(src_));
		break;
	case kTypeFloat:
		DisplayConvertAll(ConvertToFloat(src_));
		break;
	case kTypeDouble:
		DisplayConvertAll(ConvertToDouble(src_));
		break;
	case kTypeInvalid:
		DisplayConvertAll(0);
		break;
	default:
		break;
	}
}

#include "ScalarConverter.hpp"
#include "color.hpp"
#include <cctype>  // isprint
#include <cstdlib> // strtod
#include <iomanip> // fixed
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

// float || double
template <typename T>
void ScalarConverter::SetFixed(const T &t) {
	oss_ << std::fixed << std::setprecision(kPrecision) << t;
}

template <typename T>
void ScalarConverter::SetToChar(const T &scalar) {
	if (!IsCharRange(scalar)) {
		SetImpossible();
		return;
	}
	const char c = static_cast<char>(scalar);
	if (std::isprint(c)) {
		oss_ << "'" << c << "'" << std::endl;
	} else {
		oss_ << COLOR_BLUE << kMessageNonDisplayable << COLOR_END << std::endl;
	}
}

template <typename T>
void ScalarConverter::SetToInteger(const T &scalar) {
	if (!IsIntegerRange(scalar)) {
		SetImpossible();
		return;
	}
	oss_ << static_cast<int>(scalar) << std::endl;
}

template <typename T>
void ScalarConverter::SetToFloat(const T &scalar) {
	if (!IsFloatRange(scalar)) {
		SetImpossible();
		return;
	}
	SetFixed(static_cast<float>(scalar));
	oss_ << "f" << std::endl;
}

template <typename T>
void ScalarConverter::SetToDouble(const T &scalar) {
	SetFixed(static_cast<double>(scalar));
	oss_ << std::endl;
}

// ----------------------------------------------------------------------------
template <typename T>
void ScalarConverter::DisplayAll(const T scalar) {
	typedef void (*SetConvertFunc)(const T &);
	static const std::pair<const std::string, SetConvertFunc> types[] = {
		std::make_pair("char", &SetToChar<T>),
		std::make_pair("int", &SetToInteger<T>),
		std::make_pair("float", &SetToFloat<T>),
		std::make_pair("double", &SetToDouble<T>)
	};
	const unsigned int size = sizeof(types) / sizeof(*types);

	for (unsigned int i = 0; i < size; i++) {
		oss_ << types[i].first << ": ";
		if (type_ == kTypeInvalid) {
			SetImpossible();
		} else {
			types[i].second(scalar);
		}
		std::cout << oss_.str();
		oss_.str("");
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
		DisplayAll(ConvertToChar(src_));
		break;
	case kTypeInt:
		DisplayAll(ConvertToInteger(src_));
		break;
	case kTypeFloat:
		DisplayAll(ConvertToFloat(src_));
		break;
	case kTypeDouble:
		DisplayAll(ConvertToDouble(src_));
		break;
	case kTypeInvalid:
		DisplayAll(0); // unused argument
		break;
	default:
		break;
	}
}

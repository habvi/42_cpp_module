#include "ScalarConverter.hpp"
#include "color.hpp"
#include <cctype>  // isprint
#include <cstdlib> // strtod
#include <iomanip> // fixed
#include <iostream>

const std::string  ScalarConverter::kMessageImpossible     = "impossible";
const std::string  ScalarConverter::kMessageNonDisplayable = "Non displayable";
std::ostringstream ScalarConverter::oss_;

// ----------------------------------------------------------------------------
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &c) {
	(void)c;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &c) {
	(void)c;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

// ----------------------------------------------------------------------------
ScalarConverter::Type ScalarConverter::SetType(const std::string &src) {
	if (IsTypeChar(src)) {
		return kTypeChar;
	} else if (IsTypeInteger(src)) {
		return kTypeInt;
	} else if (IsTypeFloat(src)) {
		return kTypeFloat;
	} else if (IsTypeDouble(src)) {
		return kTypeDouble;
	} else {
		return kTypeInvalid;
	}
}

// ----------------------------------------------------------------------------
template <typename T>
bool ScalarConverter::IsValidRange(const double &num) {
	return std::numeric_limits<T>::min() <= num &&
		   num <= std::numeric_limits<T>::max();
}

template <typename T>
bool ScalarConverter::IsCharRange(const Type type, const T &scalar) {
	if (!IsIntegerRange(type, scalar)) {
		return false;
	}
	return IsValidRange<char>(scalar);
}

template <typename T>
bool ScalarConverter::IsIntegerRange(const Type type, const T &scalar) {
	if (type == kTypeFloat && !IsIntegerRangeForFloat(scalar)) {
		return false;
	}
	if (type == kTypeDouble && !IsValidRange<int>(scalar)) {
		return false;
	}
	return true;
}

template <typename T>
bool ScalarConverter::IsFloatRange(const T &scalar) {
	if (IsInfinityOrNan(scalar)) {
		return true;
	}
	return -std::numeric_limits<float>::max() <= scalar &&
		   scalar <= std::numeric_limits<float>::max();
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
void ScalarConverter::SetToChar(const Type type, const T &scalar) {
	if (!IsCharRange(type, scalar)) {
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
void ScalarConverter::SetToInteger(const Type type, const T &scalar) {
	if (!IsIntegerRange(type, scalar)) {
		SetImpossible();
		return;
	}
	oss_ << static_cast<int>(scalar) << std::endl;
}

template <typename T>
void ScalarConverter::SetToFloat(const Type type, const T &scalar) {
	(void)type;
	if (!IsFloatRange(scalar)) {
		SetImpossible();
		return;
	}
	SetFixed(static_cast<float>(scalar));
	oss_ << "f" << std::endl;
}

template <typename T>
void ScalarConverter::SetToDouble(const Type type, const T &scalar) {
	(void)type;
	SetFixed(static_cast<double>(scalar));
	oss_ << std::endl;
}

// ----------------------------------------------------------------------------
template <typename T>
void ScalarConverter::DisplayAll(const Type type, const T scalar) {
	typedef void (*SetConvertFunc)(const Type type, const T &);
	static const std::pair<const std::string, SetConvertFunc> types[] = {
		std::make_pair("char", &SetToChar<T>),
		std::make_pair("int", &SetToInteger<T>),
		std::make_pair("float", &SetToFloat<T>),
		std::make_pair("double", &SetToDouble<T>)
	};
	const unsigned int size = sizeof(types) / sizeof(*types);

	for (unsigned int i = 0; i < size; i++) {
		oss_ << types[i].first << ": ";
		if (type == kTypeInvalid) {
			SetImpossible();
		} else {
			types[i].second(type, scalar);
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

void ScalarConverter::convert(const std::string &src) {
	const Type type = SetType(src);

	switch (type) {
	case kTypeChar:
		DisplayAll(type, ConvertToChar(src));
		break;
	case kTypeInt:
		DisplayAll(type, ConvertToInteger(src));
		break;
	case kTypeFloat:
		DisplayAll(type, ConvertToFloat(src));
		break;
	case kTypeDouble:
		DisplayAll(type, ConvertToDouble(src));
		break;
	case kTypeInvalid:
		DisplayAll(type, 0); // unused argument
		break;
	default:
		break;
	}
}

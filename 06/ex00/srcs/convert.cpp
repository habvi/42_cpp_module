#include "ScalarConverter.hpp"
#include "color.hpp"
#include "utils.hpp"
#include <cctype> // isprint
#include <iostream>

static bool IsCharRange(const int num) {
	return std::numeric_limits<char>::min() <= num &&
		   num <= std::numeric_limits<char>::max();
}

template <typename T>
void ScalarConverter::SetToChar(const T &num) {
	const char c = static_cast<char>(num);
	if (std::isprint(c)) {
		oss_ << "'" << c << "'" << std::endl;
	} else {
		oss_ << COLOR_BLUE << kMessageNonDisplayable << COLOR_END << std::endl;
	}
}

template void ScalarConverter::SetConvertToChar<char>(const char &);
template void ScalarConverter::SetConvertToChar<int>(const int &);
template void ScalarConverter::SetConvertToChar<float>(const float &);
template void ScalarConverter::SetConvertToChar<double>(const double &);
template <typename T>
void ScalarConverter::SetConvertToChar(const T &scalar) {
	if (type_ == kTypeFloat) {
		if (!IsIntegerRange(static_cast<float>(scalar)) ||
			!IsSame(scalar, static_cast<int>(scalar))) {
			SetImpossible();
			return;
		}
	}
	if (type_ == kTypeDouble) {
		if (!IsIntegerRange(static_cast<double>(scalar)) ||
			!IsSame(scalar, static_cast<int>(scalar))) {
			SetImpossible();
			return;
		}
	}
	if (IsCharRange(static_cast<int>(scalar))) {
		SetToChar(scalar);
	} else {
		SetImpossible();
	}
}

template void ScalarConverter::SetConvertToInteger<char>(const char &);
template void ScalarConverter::SetConvertToInteger<int>(const int &);
template void ScalarConverter::SetConvertToInteger<float>(const float &);
template void ScalarConverter::SetConvertToInteger<double>(const double &);
template <typename T>
void ScalarConverter::SetConvertToInteger(const T &scalar) {
	oss_ << scalar << std::endl;
}

template void ScalarConverter::SetConvertToFloat<char>(const char &);
template void ScalarConverter::SetConvertToFloat<int>(const int &);
template void ScalarConverter::SetConvertToFloat<float>(const float &);
template void ScalarConverter::SetConvertToFloat<double>(const double &);
template <typename T>
void ScalarConverter::SetConvertToFloat(const T &scalar) {
	oss_ << scalar << std::endl;
}

template void ScalarConverter::SetConvertToDouble<char>(const char &);
template void ScalarConverter::SetConvertToDouble<int>(const int &);
template void ScalarConverter::SetConvertToDouble<float>(const float &);
template void ScalarConverter::SetConvertToDouble<double>(const double &);
template <typename T>
void ScalarConverter::SetConvertToDouble(const T &scalar) {
	oss_ << scalar << std::endl;
}

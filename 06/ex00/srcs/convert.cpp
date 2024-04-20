#include "ScalarConverter.hpp"
#include "color.hpp"
#include "utils.hpp"
#include <cctype>  // isprint
#include <iomanip> // fixed

// float || double
template <typename T>
void ScalarConverter::SetFixed(const T &t) {
	oss_ << std::fixed << std::setprecision(kPrecision) << t;
}

// ----------------------------------------------------------------------------
template <typename T>
void ScalarConverter::SetToChar(const T &num) {
	const char c = static_cast<char>(num);
	if (std::isprint(c)) {
		oss_ << "'" << c << "'" << std::endl;
	} else {
		oss_ << COLOR_BLUE << kMessageNonDisplayable << COLOR_END << std::endl;
	}
}

template <typename T>
void ScalarConverter::SetToInteger(const T &num) {
	oss_ << static_cast<int>(num) << std::endl;
}

template <typename T>
void ScalarConverter::SetToFloat(const T &num) {
	SetFixed(static_cast<float>(num));
	oss_ << "f" << std::endl;
}

template <typename T>
void ScalarConverter::SetToDouble(const T &num) {
	SetFixed(static_cast<double>(num));
	oss_ << std::endl;
}

// ----------------------------------------------------------------------------
template <typename T>
bool ScalarConverter::IsCharRange(const T &scalar) {
	if (!IsIntegerRange(scalar)) {
		return false;
	}
	return IsSame(scalar, static_cast<int>(scalar)) && IsValidRange<char>(scalar);
}

template <typename T>
bool ScalarConverter::IsIntegerRange(const T &scalar) {
	if (type_ == kTypeFloat && !IsIntegerRangeForFloat(scalar)) {
		return false;
	}
	if (type_ == kTypeDouble && !IsValidRange<int>(scalar)) {
		return false;
	}
	return true;
}

template void ScalarConverter::SetConvertToChar<char>(const char &);
template void ScalarConverter::SetConvertToChar<int>(const int &);
template void ScalarConverter::SetConvertToChar<float>(const float &);
template void ScalarConverter::SetConvertToChar<double>(const double &);
template <typename T>
void ScalarConverter::SetConvertToChar(const T &scalar) {
	if (IsCharRange(scalar)) {
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
	if (IsIntegerRange(scalar)) {
		SetToInteger(scalar);
	} else {
		SetImpossible();
	}
}

template void ScalarConverter::SetConvertToFloat<char>(const char &);
template void ScalarConverter::SetConvertToFloat<int>(const int &);
template void ScalarConverter::SetConvertToFloat<float>(const float &);
template void ScalarConverter::SetConvertToFloat<double>(const double &);
template <typename T>
void ScalarConverter::SetConvertToFloat(const T &scalar) {
	if (IsInfinityOrNan(scalar) || IsFloatRange(scalar)) {
		SetToFloat(scalar);
	} else {
		SetImpossible();
	}
}

template void ScalarConverter::SetConvertToDouble<char>(const char &);
template void ScalarConverter::SetConvertToDouble<int>(const int &);
template void ScalarConverter::SetConvertToDouble<float>(const float &);
template void ScalarConverter::SetConvertToDouble<double>(const double &);
template <typename T>
void ScalarConverter::SetConvertToDouble(const T &scalar) {
	SetToDouble(scalar);
}

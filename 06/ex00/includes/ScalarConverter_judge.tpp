#include "utils.hpp"
#include <limits>

template <typename T>
bool ScalarConverter::IsValidRange(const double &num) {
	return std::numeric_limits<T>::min() <= num &&
		   num <= std::numeric_limits<T>::max();
}

template <typename T>
bool ScalarConverter::IsCharRange(const T &scalar) {
	if (!IsIntegerRange(scalar)) {
		return false;
	}
	// todo: issame iru?
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

template <typename T>
bool ScalarConverter::IsFloatRange(const T &scalar) {
	if (IsInfinityOrNan(scalar)) {
		return true;
	}
	return -std::numeric_limits<float>::max() <= scalar &&
		   scalar <= std::numeric_limits<float>::max();
}

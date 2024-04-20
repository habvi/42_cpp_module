#include "ScalarConverter.hpp"
#include "utils.hpp"
#include <cctype> // isdigit,tolower
#include <cerrno>
#include <cstdlib> // strtod
#include <limits>

// ----------------------------------------------------------------------------
// utils
// ----------------------------------------------------------------------------
static double ConvertStrToDouble(const std::string &str, bool &err) {
	err = false;
	char *str_end;
	errno            = 0;
	const double num = std::strtod(str.c_str(), &str_end);
	if (errno == ERANGE) {
		err = true;
		return -1;
	}
	if (str == str_end || *str_end != '\0') {
		err = true;
		return -1;
	}
	return num;
}

static bool IsSameStr(const std::string &s1, const std::string &s2) {
	if (s1.size() != s2.size()) {
		return false;
	}
	for (size_t i = 0; i < s1.size(); i++) {
		if (std::tolower(s1[i]) != std::tolower(s2[i])) {
			return false;
		}
	}
	return true;
}

// ----------------------------------------------------------------------------
// char
// ----------------------------------------------------------------------------
// 'a' (3bytes)
bool ScalarConverter::IsTypeChar() {
	if (src_.size() != 3) {
		return false;
	}
	return src_[0] == '\'' && src_[2] == '\'';
}

// ----------------------------------------------------------------------------
// integer
// ----------------------------------------------------------------------------
bool ScalarConverter::IsIntegerRange(const float &num) {
	if (IsInfinityOrNan(num)) {
		return false;
	}
	if (num >= (std::numeric_limits<int>::max() - 1.0f) ||
		num < (std::numeric_limits<int>::min() + 1.0f) ||
		(num >= 0.0f && num < std::numeric_limits<float>::min())) {
		return false;
	}
	return true;
}

bool ScalarConverter::IsIntegerRange(const double &num) {
	// if (IsInfinityOrNan(num)) {
	// 	return false;
	// }
	return std::numeric_limits<int>::min() <= num &&
		   num <= std::numeric_limits<int>::max();
}

// ok : INT_MIN～INT_MAX
// ng : out_of_range / 12.3f / 12.3 / "  123" / inf / nan
bool ScalarConverter::IsTypeInteger() {
	size_t head = 0;
	if (src_[head] == '-' || src_[head] == '+') {
		head++;
	}
	for (size_t i = head; i < src_.size(); i++) {
		if (!std::isdigit(src_[i])) {
			return false;
		}
	}
	bool         err;
	const double num = ConvertStrToDouble(src_, err);
	if (err) {
		return false;
	}
	return IsIntegerRange(num);
}

// ----------------------------------------------------------------------------
// float
// ----------------------------------------------------------------------------
template bool ScalarConverter::IsFloatRange<char>(const char &);
template bool ScalarConverter::IsFloatRange<int>(const int &);
template bool ScalarConverter::IsFloatRange<float>(const float &);
template bool ScalarConverter::IsFloatRange<double>(const double &);
template <typename T>
bool ScalarConverter::IsFloatRange(const T &num) {
	if (IsInfinityOrNan(num)) {
		return true;
	}
	return -std::numeric_limits<float>::max() <= num &&
		   num <= std::numeric_limits<float>::max();
}

// ok : -FLT_MAX～FLT_MAX / inff / -INFF / nanf / -NAnf
// ng : out_of_range / 12.3(no f) / "  123f" / inf / nan
bool ScalarConverter::IsTypeFloat() {
	std::string::size_type pos_f = src_.rfind("f");
	std::string::size_type pos_F = src_.rfind("F");
	if (!(pos_f != std::string::npos || pos_F != std::string::npos)) {
		return false;
	}
	const std::string except_tail_f = src_.substr(0, src_.size() - 1);
	if (!IsTypeDouble(except_tail_f)) {
		return false;
	}
	bool         err;
	const double num = ConvertStrToDouble(except_tail_f, err);
	if (err) {
		return false;
	}
	return IsFloatRange(num);
}

// ----------------------------------------------------------------------------
// double
// ----------------------------------------------------------------------------
static bool IsInfinityOrNanStr(const std::string &s) {
	static const std::string infs[] = {
		"inf",
		"infinity",
		"nan",
	};
	const size_t size = sizeof(infs) / sizeof(*infs);

	for (size_t i = 0; i < size; i++) {
		if (IsSameStr(s, infs[i])) {
			return true;
		}
	}
	return false;
}

// ok : -DBL_MAX～DBL_MAX / inf / nan
// ng : out_of_range / 12.3f / "  123" / inff / nanf
bool ScalarConverter::IsTypeDouble() {
	size_t head = 0;
	if (src_[head] == '-' || src_[head] == '+') {
		head++;
	}
	if (IsInfinityOrNanStr(&src_[head])) {
		return true;
	}
	for (size_t i = head; i < src_.size(); i++) {
		if (!(std::isdigit(src_[i]) || src_[i] == '.')) {
			return false;
		}
	}
	bool err;
	ConvertStrToDouble(src_, err);
	return err == false;
}

bool ScalarConverter::IsTypeDouble(const std::string &str) {
	size_t head = 0;
	if (str[head] == '-' || str[head] == '+') {
		head++;
	}
	if (IsInfinityOrNanStr(&str[head])) {
		return true;
	}
	for (size_t i = head; i < str.size(); i++) {
		if (!(std::isdigit(str[i]) || str[i] == '.')) {
			return false;
		}
	}
	bool err;
	ConvertStrToDouble(str, err);
	return err == false;
}

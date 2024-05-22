#include "ScalarConverter.hpp"
#include <cctype> // isdigit
#include <cerrno>
#include <cstdlib> // strtod

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

// ----------------------------------------------------------------------------
// char
// ----------------------------------------------------------------------------
// 'a' (3bytes)
bool ScalarConverter::IsTypeChar(const std::string &src) {
	if (src.size() != 3) {
		return false;
	}
	return src[0] == '\'' && src[2] == '\'';
}

// ----------------------------------------------------------------------------
// integer
// ----------------------------------------------------------------------------
bool ScalarConverter::IsIntegerRangeForFloat(const float &num) {
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

// ok : INT_MIN～INT_MAX
// ng : out_of_range / 12.3f / 12.3 / "  123" / inf / nan
bool ScalarConverter::IsTypeInteger(const std::string &src) {
	size_t head = 0;
	if (src[head] == '-' || src[head] == '+') {
		head++;
	}
	for (size_t i = head; i < src.size(); i++) {
		if (!std::isdigit(src[i])) {
			return false;
		}
	}
	bool         err;
	const double num = ConvertStrToDouble(src, err);
	if (err) {
		return false;
	}
	return IsValidRange<int>(num);
}

// ----------------------------------------------------------------------------
// float
// ----------------------------------------------------------------------------
// ok : -FLT_MAX～FLT_MAX / inff / -INFF / nanf / -NAnf
// ng : out_of_range / 12.3(no f) / "  123f" / inf / nan
bool ScalarConverter::IsTypeFloat(const std::string &src) {
	std::string::size_type pos_f = src.rfind("f");
	std::string::size_type pos_F = src.rfind("F");
	if (!(pos_f != std::string::npos || pos_F != std::string::npos)) {
		return false;
	}
	const std::string except_tail_f = src.substr(0, src.size() - 1);
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
static bool IsInfinityOrNanStr(const std::string &src) {
	static const std::string infs[] = {
		"-inf",
		"+inf",
		"nan",
	};
	const size_t size = sizeof(infs) / sizeof(*infs);

	for (size_t i = 0; i < size; i++) {
		if (src == infs[i]) {
			return true;
		}
	}
	return false;
}

// ok : -DBL_MAX～DBL_MAX / inf / nan
// ng : out_of_range / 12.3f / "  123" / inff / nanf
bool ScalarConverter::IsTypeDouble(const std::string &src) {
	if (IsInfinityOrNanStr(src)) {
		return true;
	}
	size_t head = 0;
	if (src[head] == '-' || src[head] == '+') {
		head++;
	}
	for (size_t i = head; i < src.size(); i++) {
		if (!(std::isdigit(src[i]) || src[i] == '.')) {
			return false;
		}
	}
	bool err;
	ConvertStrToDouble(src, err);
	return err == false;
}

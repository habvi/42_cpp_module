#include "ScalarConverter.hpp"
#include <cctype> // isdigit
#include <cerrno>
#include <cstdlib> // strtod
#include <iostream>
#include <limits>

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

// 'a' (3bytes)
bool ScalarConverter::IsTypeChar() {
	if (src_.size() != 3) {
		return false;
	}
	return src_[0] == '\'' && src_[2] == '\'';
}

double ScalarConverter::ConvertStrToDouble(bool &err) {
	err = false;
	char *str_end;
	errno            = 0;
	const double num = std::strtod(src_.c_str(), &str_end);
	if (errno == ERANGE) {
		err = true;
		return -1;
	}
	if (src_ == str_end || *str_end != '\0') {
		err = true;
		return -1;
	}
	return num;
}

bool ScalarConverter::IsIntegerRange(const double &num) {
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
	const double num = ConvertStrToDouble(err);
	if (err) {
		return false;
	}
	return IsIntegerRange(num);
}

static bool IsNan(const double &num) {
	return num != num;
}

static bool IsInfinity(const double &num) {
	static const double inf = std::numeric_limits<double>::infinity();
	return num == inf || num == -inf;
}

static bool IsInfinityOrNan(const double &num) {
	return IsInfinity(num) || IsNan(num);
}

static bool IsFloatRange(const double &num) {
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
	std::string except_tail_f = src_.substr(0, src_.size() - 1);
	src_                      = except_tail_f;
	if (!IsTypeDouble()) {
		return false;
	}
	bool         err;
	const double num = ConvertStrToDouble(err);
	if (err) {
		return false;
	}
	return IsFloatRange(num);
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

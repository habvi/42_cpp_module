#include "ScalarConverter.hpp"
#include "color.hpp"
#include <cerrno>
#include <cstdlib> // strtod
#include <iostream>
#include <limits>

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

// 'a' (3bytes)
bool ScalarConverter::IsTypeChar() {
	if (src_.size() != 3) {
		return false;
	}
	return src_[0] == '\'' && src_[2] == '\'';
}

double ScalarConverter::ConvertStrToDouble(const std::string &str, bool &err) {
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
	const double num = ConvertStrToDouble(src_, err);
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
	ConvertStrToDouble(src_, err);
	return err == false;
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

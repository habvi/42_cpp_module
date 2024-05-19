#include "RPN.hpp"
#include <cctype>  // isdigit
#include <cstring> // strchr
#include <limits>
#include <sstream>
#include <stack>
#include <stdexcept>

const char       *RPN::kOperations            = "+-/*";
const std::string RPN::kErrMsgInvalidArgument = "invalid argument";

RPN::RPN() {}

RPN::RPN(const RPN &other) {
	(void)other;
}

RPN &RPN::operator=(const RPN &other) {
	(void)other;
	return *this;
}

RPN::~RPN() {}

namespace {
	static const int kIntMax = std::numeric_limits<int>::max();
	static const int kIntMin = std::numeric_limits<int>::min();

	bool MyIsDigit(const char c) {
		return std::isdigit(static_cast<unsigned char>(c));
	}

	int ConvertToInt(const char c) {
		std::stringstream ss;
		ss << c;
		int num;
		ss >> num;
		return num;
	}

	// stack.size() >= 1
	int PopBack(std::stack<int> &s) {
		const int tmp_num = s.top();
		s.pop();
		return tmp_num;
	}

	bool IsOverflowAdd(const int num1, const int num2) {
		if (num2 > 0) {
			return num1 > kIntMax - num2;
		} else {
			return num1 < kIntMin - num2;
		}
	}

	bool IsOverflowSub(const int num1, const int num2) {
		if (num2 > 0) {
			return num1 < kIntMin + num2;
		} else {
			return num1 > kIntMax + num2;
		}
	}

	bool IsOverflowDiv(const int num1, const int num2) {
		return num1 == kIntMin && num2 == -1;
	}

	bool IsOverflowMul(const int num1, const int num2) {
		if (num1 == 0 || num2 == 0) {
			return false;
		}
		if (num1 > 0 && num2 > 0) {
			if (num1 > kIntMax / num2) {
				return true;
			}
		}
		if (num1 < 0 && num2 < 0) {
			return num1 < kIntMax / num2;
		}
		if (num1 > 0) {
			return num2 < kIntMin / num1;
		} else {
			return num1 < kIntMin / num2;
		}
		return false;
	}

	int EvalArithmeticOperation(const int num1, const char op, const int num2) {
		static const std::string kErrMsgOverflowArgument = "overflow argument";

		if (op == '+') {
			if (IsOverflowAdd(num1, num2)) {
				throw std::overflow_error(kErrMsgOverflowArgument);
			}
			return num1 + num2;
		} else if (op == '-') {
			if (IsOverflowSub(num1, num2)) {
				throw std::overflow_error(kErrMsgOverflowArgument);
			}
			return num1 - num2;
		} else if (op == '/') {
			if (num2 == 0) {
				throw std::runtime_error("division by zero");
			}
			if (IsOverflowDiv(num1, num2)) {
				throw std::overflow_error(kErrMsgOverflowArgument);
			}
			return num1 / num2;
		} else {
			if (IsOverflowMul(num1, num2)) {
				throw std::overflow_error(kErrMsgOverflowArgument);
			}
			return num1 * num2;
		}
	}
} // namespace

bool RPN::IsOperations(const char c) {
	return std::strchr(kOperations, c);
}

bool RPN::IsValidStr(const std::string &str) {
	for (std::size_t i = 0; i < str.size(); i++) {
		const char ch = str[i];
		if (!MyIsDigit(ch) && !IsOperations(ch) && ch != ' ') {
			return false;
		}
	}
	return true;
}

// ex) "1 2 3 + -"
// stack
// 1
// 1 2
// 1 2 3
// 1 2 3 +
// 1 5
// 1 5 -
// -4
int RPN::Calcurate(const std::string &rpn_str) {
	if (!IsValidStr(rpn_str)) {
		throw std::invalid_argument(kErrMsgInvalidArgument);
	}

	std::stack<int> num_stack;
	for (std::size_t i = 0; i < rpn_str.size(); i++) {
		const char ch = rpn_str[i];
		if (MyIsDigit(ch)) {
			num_stack.push(ConvertToInt(ch));
		} else if (IsOperations(ch)) {
			if (num_stack.size() < 2) {
				throw std::invalid_argument(kErrMsgInvalidArgument);
			}
			const int num2 = PopBack(num_stack);
			const int num1 = PopBack(num_stack);
			num_stack.push(EvalArithmeticOperation(num1, ch, num2));
		}
	}
	if (num_stack.size() != 1) {
		throw std::invalid_argument(kErrMsgInvalidArgument);
	}
	return num_stack.top();
}

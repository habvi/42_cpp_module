#include "RPN.hpp"
#include <cctype>   // isdigit
#include <cstring>  // strchr
#include <sstream>
#include <stack>
#include <stdexcept>

const char *kOperations = "+-/*";

RPN::RPN() {}

RPN::RPN(const RPN &other) {
	(void)other;
}

RPN &RPN::operator=(const RPN &other) {
	if (this != &other) {
	}
	return *this;
}

RPN::~RPN() {}

namespace {
	bool MyIsDigit(const char c) {
		return std::isdigit(static_cast<unsigned char>(c));
	}

	bool IsOperations(const char c) {
		return std::strchr(kOperations, c);
	}

	bool IsValidStr(const std::string &str) {
		(void)str;
		return true;
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

	int Eval(const int num1, const char op, const int num2) {
		if (op == '+') {
			// todo: overflow
			return num1 + num2;
		} else if (op == '-') {
			// todo: overflow
			return num1 - num2;
		} else if (op == '/') {
			// todo: zero division
			return num1 / num2;
		} else {
			// todo: overflow
			return num1 * num2;
		}
	}
} // namespace

int RPN::Calcurate(const std::string &rpn_str) {
	if (!IsValidStr(rpn_str)) {
		throw std::invalid_argument("invalid argument");
	}

	std::stack<int> num_stack;
	for (std::size_t i = 0; i < rpn_str.size(); i++) {
		const char ch = rpn_str[i];
		if (MyIsDigit(ch)) {
			const int num = ConvertToInt(ch);
			num_stack.push(num);
		} else if (IsOperations(ch)) {
			if (num_stack.size() < 2) {
				throw std::invalid_argument("invalid argument");
			}
			const int num2        = PopBack(num_stack);
			const int num1        = PopBack(num_stack);
			const int calc_result = Eval(num1, ch, num2);
			num_stack.push(calc_result);
		}
	}
	if (num_stack.size() != 1) {
		throw std::invalid_argument("invalid argument");
	}
	return num_stack.top();
}

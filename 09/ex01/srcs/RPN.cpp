#include "RPN.hpp"

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

int RPN::Calcurate(const std::string &str) {
	(void)str;
	return 1;
}

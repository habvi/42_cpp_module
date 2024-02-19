#include "Fixed.hpp"
#include <iomanip>
#include <iostream>

#define COLOR_RED   "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_END   "\033[0m"

static void DisplayTitle(const std::string &title) {
	std::cout << std::endl;
	std::cout << "┃ Test: " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void Line() {
	std::cout << "--------------------------------" << std::endl;
}

static void JudgeIsEqual(const bool x, const bool y) {
	std::cout << (x == y ? COLOR_GREEN "OK" : COLOR_RED "NG") << COLOR_END
			  << std::endl;
}

template <typename T, typename U>
static void RunArithmeticOperatorsTest(T x, U y) {
	std::cout << std::fixed << std::setprecision(8);
	std::cout << x << " + " << y << " = " << (Fixed(x) + Fixed(y)) << std::endl;
	std::cout << x << " + " << y << " = " << x + y << std::endl;
	std::cout << x << " - " << y << " = " << (Fixed(x) - Fixed(y)) << std::endl;
	std::cout << x << " - " << y << " = " << x - y << std::endl;
	std::cout << x << " * " << y << " = " << (Fixed(x) * Fixed(y)) << std::endl;
	std::cout << x << " * " << y << " = " << x * y << std::endl;
	std::cout << x << " / " << y << " = " << (Fixed(x) / Fixed(y)) << std::endl;
	std::cout << x << " / " << y << " = " << x / y << std::endl;
	Line();
}

template <typename T, typename U>
static void RunComparisonOperatorsTest(T x, U y) {
	std::cout << std::fixed << std::setprecision(8);
	std::cout << x << " < " << y << " -> ";
	JudgeIsEqual((Fixed(x) < Fixed(y)), (x < y));
	std::cout << x << " > " << y << " -> ";
	JudgeIsEqual((Fixed(x) > Fixed(y)), (x > y));
	std::cout << x << " <= " << y << " -> ";
	JudgeIsEqual((Fixed(x) <= Fixed(y)), (x <= y));
	std::cout << x << " >= " << y << " -> ";
	JudgeIsEqual((Fixed(x) >= Fixed(y)), (x >= y));
	std::cout << x << " == " << y << " -> ";
	JudgeIsEqual((Fixed(x) == Fixed(y)), (x == y));
	std::cout << x << " != " << y << " -> ";
	JudgeIsEqual((Fixed(x) != Fixed(y)), (x != y));
}

static void RunOriginalTest() {
	std::cout << "\n------------ original ------------" << std::endl;

	// arithmetic operators "+, -, *, /" overload
	DisplayTitle("arithmetic operators");
	RunArithmeticOperatorsTest(5.05f, 2);
	RunArithmeticOperatorsTest(5.05f, 20);
	RunArithmeticOperatorsTest(5, 2.123f);
	RunArithmeticOperatorsTest(5, 20.123f);
	RunArithmeticOperatorsTest(1, 0.0123f);
	RunArithmeticOperatorsTest(2147483647 / 2, 2147483647.f / 2);

	// comparison operators ">, <, >=, <=, ==, !=" overload
	DisplayTitle("comparison operators");
	RunComparisonOperatorsTest(5.05f, 2);
	RunComparisonOperatorsTest(5, 5.0f);
	RunComparisonOperatorsTest(5.0f, 1234.000f);
	RunComparisonOperatorsTest(5.0f, 5.0f);
	RunComparisonOperatorsTest(1, 500);
	RunComparisonOperatorsTest(123456, 123456);
}

int main() {
	Fixed       a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	// std::cout << ++a << std::endl;
	// std::cout << a << std::endl;
	// std::cout << a++ << std::endl;
	// std::cout << a << std::endl;

	std::cout << b << std::endl;

	// std::cout << Fixed::max(a, b) << std::endl;

	RunOriginalTest();

	return 0;
}

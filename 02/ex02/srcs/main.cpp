#include "Fixed.hpp"
#include <iomanip>
#include <iostream>

static void DisplayTitle(const std::string &title) {
	std::cout << "┃ Test: " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void Line() {
	std::cout << "--------------------------------" << std::endl;
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

static void RunOriginalTest() {
	std::cout << "\n------------ original ------------\n" << std::endl;

	// arithmetic operators "+, -, *, /" overload
	DisplayTitle("arithmetic operators");
	RunArithmeticOperatorsTest(5.05f, 2);
	RunArithmeticOperatorsTest(5.05f, 20);
	RunArithmeticOperatorsTest(5, 2.123f);
	RunArithmeticOperatorsTest(5, 20.123f);
	RunArithmeticOperatorsTest(1, 0.0123f);
	RunArithmeticOperatorsTest(2147483647 / 2, 2147483647.f / 2);
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

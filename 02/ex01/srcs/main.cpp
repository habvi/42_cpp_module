#include "Fixed.hpp"
#include <iostream>

/*
#include <iomanip>

static void RunInt(const int number) {
	std::cout << "-------------------------" << std::endl;
	const Fixed f(number);

	std::cout << std::fixed << std::setprecision(10);
	std::cout << "number : " << number << std::endl;
	std::cout << "float  : " << f << std::endl;
	std::cout << "int    : " << f.toInt() << std::endl;
}

static void RunFloat(const float number) {
	std::cout << "-------------------------" << std::endl;
	const Fixed f(number);

	std::cout << std::fixed << std::setprecision(10);
	std::cout << "number : " << number << std::endl;
	std::cout << "float  : " << f << std::endl;
	std::cout << "int    : " << f.toInt() << std::endl;
}

static void RunOriginalTest() {
	std::cout << "\n----- original test -----" << std::endl;
	RunInt(0);
	RunInt(12345);
	RunInt(2147483647);
	RunInt(-2147483648);
	RunInt(-12345);
	RunInt(2147483647 >> 8);
	RunInt((2147483647 >> 8) + 1);
	RunInt(-2147483648 >> 8);
	RunInt((-2147483648 >> 8) - 1);

	RunFloat(0.0f);
	RunFloat(0.123f);
	RunFloat(123.0f);
	RunFloat(1.23456789f);
	RunFloat(1234567.89f);
	RunFloat(123456789.0f);
	RunFloat(0.123456789f);
}
*/

int main() {
	Fixed       a;
	Fixed const b(10);
	Fixed const c(42.42f);
	Fixed const d(b);

	a = Fixed(1234.4321f);

	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;

	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;

	// RunOriginalTest();

	return 0;
}

#include "Fixed.hpp"
#include <climits>
#include <iomanip>
#include <iostream>

static void RunInt(const int number) {
	std::cout << "-------------------------" << std::endl;
	const Fixed f(number);

	std::cout << std::fixed << std::setprecision(8);
	std::cout << "number : " << number << std::endl;
	std::cout << "rawbit : " << f.getRawBits() << std::endl;
	std::cout << "float  : " << f << std::endl;
	std::cout << "int    : " << f.toInt() << std::endl;
}

static void RunFloat(const float number) {
	std::cout << "-------------------------" << std::endl;
	const Fixed f(number);

	std::cout << std::fixed << std::setprecision(8);
	std::cout << "number : " << number << std::endl;
	std::cout << "rawbit : " << f.getRawBits() << std::endl;
	std::cout << "float  : " << f << std::endl;
	std::cout << "int    : " << f.toInt() << std::endl;
}

static void RunOriginalTest() {
	std::cout << "\n----- original test -----" << std::endl;
	static const int   kNumOfFractionalBits  = 8;
	static const float MinRepresentableFloat = 1.f / (1 << kNumOfFractionalBits);

	// int
	RunInt(0);
	RunInt(12345);
	RunInt(INT_MAX);
	RunInt(INT_MIN);
	RunInt(-12345);
	RunInt(INT_MAX >> kNumOfFractionalBits);
	RunInt((INT_MAX >> kNumOfFractionalBits) + 1);
	RunInt(INT_MIN >> kNumOfFractionalBits);
	RunInt((INT_MIN >> kNumOfFractionalBits) - 1);

	// float
	RunFloat(0.0f);
	RunFloat(0.123f);
	RunFloat(123.0f);
	RunFloat(1.23456789f);
	RunFloat(1234567.89f);
	RunFloat(123456789.0f);
	RunFloat(-0.123456789f);
	RunFloat(0.123456789f);

	// 0000 0000 0000 0000 0000 0000 0111 1011.1111 1111
	RunFloat(123.99609375f);
	// 0000 0000 0000 0000 0000 0000 0111 1011.1111 1110   (123.9921875)
	RunFloat(123.99609375f - MinRepresentableFloat);
	// 0000 0000 0000 0000 0000 0000 0111 1011.1111 1110 1 (123.994140625)
	RunFloat(123.99609375f - MinRepresentableFloat / 2);
	// 0000 0000 0111 1111 1111 1111 1111 1111.1111 1111
	RunFloat(8388607.99609375f);
	// 0000 0000 0000 0000 1111 1111 1111 1111.1111 1111
	RunFloat(65535.99609375f);
	// 0000 0000 0000 0001 0000 0000 0000 0000.0000 0000
	RunFloat(65535.99609375f + MinRepresentableFloat);
}

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

	RunOriginalTest();

	return 0;
}

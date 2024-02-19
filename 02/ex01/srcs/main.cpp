#include "Fixed.hpp"
#include <climits>
#include <iomanip>
#include <iostream>

template <typename T>
static void RunFixed(T x) {
	std::cout << "-------------------------" << std::endl;
	const Fixed f(x);

	std::cout << std::fixed << std::setprecision(8);
	std::cout << "number : " << x << std::endl;
	std::cout << "rawbit : " << f.getRawBits() << std::endl;
	std::cout << "float  : " << f << std::endl;
	std::cout << "int    : " << f.toInt() << std::endl;
}

static void RunOriginalTest() {
	std::cout << "\n----- original test -----" << std::endl;
	static const int   kNumOfFractionalBits  = 8;
	static const float MinRepresentableFloat = 1.f / (1 << kNumOfFractionalBits);

	// int
	RunFixed(0);
	RunFixed(12345);
	RunFixed(INT_MAX);
	RunFixed(INT_MIN);
	RunFixed(-12345);
	RunFixed(INT_MAX >> kNumOfFractionalBits);
	RunFixed((INT_MAX >> kNumOfFractionalBits) + 1);
	RunFixed(INT_MIN >> kNumOfFractionalBits);
	RunFixed((INT_MIN >> kNumOfFractionalBits) - 1);

	// float
	RunFixed(0.0f);
	RunFixed(0.123f);
	RunFixed(123.0f);
	RunFixed(1.23456789f);
	RunFixed(1234567.89f);
	RunFixed(123456789.0f);
	RunFixed(-0.123456789f);
	RunFixed(0.123456789f);

	// 0000 0000 0000 0000 0000 0000 0111 1011.1111 1111
	RunFixed(123.99609375f);
	// 0000 0000 0000 0000 0000 0000 0111 1011.1111 1110   (123.9921875)
	RunFixed(123.99609375f - MinRepresentableFloat);
	// 0000 0000 0000 0000 0000 0000 0111 1011.1111 1110 1 (123.994140625)
	RunFixed(123.99609375f - MinRepresentableFloat / 2);
	// 0000 0000 0111 1111 1111 1111 1111 1111.1111 1111
	RunFixed(8388607.99609375f);
	// 0000 0000 0000 0000 1111 1111 1111 1111.1111 1111
	RunFixed(65535.99609375f);
	// 0000 0000 0000 0001 0000 0000 0000 0000.0000 0000
	RunFixed(65535.99609375f + MinRepresentableFloat);
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

#include "Fixed.hpp"
#include <iomanip>
#include <iostream>

#define COLOR_RED              "\033[31m"
#define COLOR_GREEN            "\033[32m"
#define COLOR_END              "\033[0m"

#define NUM_OF_FRACTIONAL_BITS 8

static void DisplayTitle(const std::string &title) {
	std::cout << std::endl;
	std::cout << "┃ Test: " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void Line() {
	std::cout << "--------------------------------" << std::endl;
}

template <typename T, typename U>
static void JudgeIsEqual(T x, U y) {
	std::cout << "(x: " << x << ") (y: " << y << ") ";
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

template <typename T>
static void RunIncrementDecrementOperatorsTest(T x) {
	T tmp_x = x;
	T tmp_y = x;

	static const float kMinRepresentableFloat = 1.f / (1 << NUM_OF_FRACTIONAL_BITS);

	std::cout << std::fixed << std::setprecision(8);

	std::cout << "Fixed(" << tmp_x << ")++" << std::endl;
	Fixed f(tmp_x);
	std::cout << "  -> before: ";
	JudgeIsEqual(f, tmp_y);
	std::cout << "  -> ++    : ";
	JudgeIsEqual(f++, tmp_y);
	std::cout << "  -> after : ";
	JudgeIsEqual(f, tmp_y + kMinRepresentableFloat);

	f = Fixed(tmp_x);
	std::cout << "++Fixed(" << tmp_x << ")" << std::endl;
	std::cout << "  -> before: ";
	JudgeIsEqual(f, tmp_y);
	std::cout << "  -> ++    : ";
	JudgeIsEqual(++f, tmp_y + kMinRepresentableFloat);
	std::cout << "  -> after : ";
	JudgeIsEqual(f, tmp_y + kMinRepresentableFloat);

	f = Fixed(tmp_x);
	std::cout << "Fixed(" << tmp_x << ")--" << std::endl;
	std::cout << "  -> before: ";
	JudgeIsEqual(f, tmp_y);
	std::cout << "  -> --    : ";
	JudgeIsEqual(f--, tmp_y);
	std::cout << "  -> after : ";
	JudgeIsEqual(f, tmp_y - kMinRepresentableFloat);

	f = Fixed(tmp_x);
	std::cout << "--Fixed(" << tmp_x << ")" << std::endl;
	std::cout << "  -> before: ";
	JudgeIsEqual(f, tmp_y);
	std::cout << "  -> --    : ";
	JudgeIsEqual(--f, tmp_y - kMinRepresentableFloat);
	std::cout << "  -> after : ";
	JudgeIsEqual(f, tmp_y - kMinRepresentableFloat);
}

template <typename T, typename U>
static float MinWithDifferentType(T x, U y) {
	return (x < y) ? static_cast<float>(x) : static_cast<float>(y);
}

template <typename T, typename U>
static float MaxWithDifferentType(T x, U y) {
	return (x > y) ? static_cast<float>(x) : static_cast<float>(y);
}

template <typename T, typename U>
static void RunMinMaxTest(T x, U y) {
	std::cout << std::fixed << std::setprecision(8);

	Fixed       a = Fixed(x);
	Fixed       b = Fixed(y);
	const Fixed c(x);
	const Fixed d(y);

	std::cout << "min(Fixed(" << x << "), Fixed(" << y << "))\n  -> ";
	JudgeIsEqual(Fixed::min(a, b), MinWithDifferentType(x, y));

	std::cout << "min(const Fixed(" << x << "), const Fixed(" << y << "))\n  -> ";
	JudgeIsEqual(Fixed::min(c, d), MinWithDifferentType(x, y));

	std::cout << "max(Fixed(" << x << "), Fixed(" << y << "))\n  -> ";
	JudgeIsEqual(Fixed::max(a, b), MaxWithDifferentType(x, y));

	std::cout << "max(const Fixed(" << x << "), const Fixed(" << y << "))\n  -> ";
	JudgeIsEqual(Fixed::max(c, d), MaxWithDifferentType(x, y));
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

	// increment/decrement "x++,++x,x--,--x" overload
	DisplayTitle("increment/decrement operators");
	RunIncrementDecrementOperatorsTest(0);
	RunIncrementDecrementOperatorsTest(2);
	RunIncrementDecrementOperatorsTest(-12345);
	RunIncrementDecrementOperatorsTest(5.05f);
	RunIncrementDecrementOperatorsTest(-123.45f);

	// min/max overloaded member functions
	DisplayTitle("min/max overloaded member functions");
	RunMinMaxTest(0, 0);
	RunMinMaxTest(0, 5.05f);
	RunMinMaxTest(5.05f, 2);
	RunMinMaxTest(5.05f, -2);
	RunMinMaxTest(-5.05f, 2);
	RunMinMaxTest(-5.05f, -2);
	RunMinMaxTest(-5.05f, -5);
	RunMinMaxTest(1, 500);
	RunMinMaxTest(1, -500);
	RunMinMaxTest(-1, 500);
	RunMinMaxTest(-1, -500);
}

int main() {
	Fixed       a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;

	// std::cout << Fixed::max(a, b) << std::endl;

	RunOriginalTest();

	return 0;
}

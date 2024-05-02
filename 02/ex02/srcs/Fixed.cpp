#include "Fixed.hpp"
#include <cmath>
#include <iostream>

// default constructor
Fixed::Fixed() : fixed_point_number_value_(0) {
#ifndef NO_DEBUG
	std::cout << "Default constructor called" << std::endl;
#endif
}

// Int constructor
Fixed::Fixed(const int number)
	: fixed_point_number_value_(number << kNumOfFractionalBits_) {
#ifndef NO_DEBUG
	std::cout << "Int constructor called" << std::endl;
#endif
}

// Float constructor
Fixed::Fixed(const float number)
	: fixed_point_number_value_(
		  static_cast<int>(roundf(number * (1 << kNumOfFractionalBits_)))
	  ) {
#ifndef NO_DEBUG
	std::cout << "Float constructor called" << std::endl;
#endif
}

// copy constructor
Fixed::Fixed(const Fixed &f) : fixed_point_number_value_(f.getRawBits()) {
#ifndef NO_DEBUG
	std::cout << "Copy constructor called" << std::endl;
#endif
}

// copy assignment operator overload
Fixed &Fixed::operator=(const Fixed &f) {
#ifndef NO_DEBUG
	std::cout << "Copy assignment operator called" << std::endl;
#endif
	if (this != &f) {
		setRawBits(f.getRawBits());
	}
	return *this;
}

// \New!/ comparison operator ">" overload
bool Fixed::operator>(const Fixed &f) const {
	return fixed_point_number_value_ > f.getRawBits();
}

// \New!/ comparison operator "<" overload
bool Fixed::operator<(const Fixed &f) const {
	return fixed_point_number_value_ < f.getRawBits();
}

// \New!/ comparison operator ">=" overload
bool Fixed::operator>=(const Fixed &f) const {
	return fixed_point_number_value_ >= f.getRawBits();
}

// \New!/ comparison operator "<=" overload
bool Fixed::operator<=(const Fixed &f) const {
	return fixed_point_number_value_ <= f.getRawBits();
}

// \New!/ comparison operator "==" overload
bool Fixed::operator==(const Fixed &f) const {
	return fixed_point_number_value_ == f.getRawBits();
}

// \New!/ comparison operator "!=" overload
bool Fixed::operator!=(const Fixed &f) const {
	return fixed_point_number_value_ != f.getRawBits();
}

// \New!/ arithmetic operator "+" overload
Fixed Fixed::operator+(const Fixed &f) const {
	Fixed tmp(*this);
	tmp += f;
	return tmp;
}

// \New!/ arithmetic operator "-" overload
Fixed Fixed::operator-(const Fixed &f) const {
	Fixed tmp(*this);
	tmp -= f;
	return tmp;
}

// \New!/ arithmetic operator "*" overload
Fixed Fixed::operator*(const Fixed &f) const {
	Fixed tmp(*this);
	tmp *= f;
	return tmp;
}

// \New!/ arithmetic operator "/" overload
Fixed Fixed::operator/(const Fixed &f) const {
	Fixed tmp(*this);
	tmp /= f;
	return tmp;
}

// \New!(not required)/ arithmetic operator "+=" overload
const Fixed &Fixed::operator+=(const Fixed &f) {
	fixed_point_number_value_ += f.getRawBits();
	return *this;
}

// \New!(not required)/ arithmetic operator "-=" overload
const Fixed &Fixed::operator-=(const Fixed &f) {
	fixed_point_number_value_ -= f.getRawBits();
	return *this;
}

// \New!(not required)/ arithmetic operator "*=" overload
const Fixed &Fixed::operator*=(const Fixed &f) {
	fixed_point_number_value_ =
		fixed_point_number_value_ * f.getRawBits() >> kNumOfFractionalBits_;
	return *this;
}

// \New!(not required)/ arithmetic operator "/=" overload
const Fixed &Fixed::operator/=(const Fixed &f) {
	fixed_point_number_value_ = fixed_point_number_value_ / f.getRawBits()
								<< kNumOfFractionalBits_;
	return *this;
}

// \New!/ pre-increment operator "++x" overload
const Fixed &Fixed::operator++() {
	fixed_point_number_value_++;
	return *this;
}

// \New!/ post-increment operator "x++" overload
// The compiler distinguishes between the pre-increment operator and the
// post-increment operator by having the post-increment operator take an int type
// dummy argument.
Fixed Fixed::operator++(int) {
	Fixed tmp(*this);
	++*this;
	return tmp;
}

// \New!/ pre-decrement operator "--x" overload
const Fixed &Fixed::operator--() {
	fixed_point_number_value_--;
	return *this;
}

// \New!/ post-decrement operator "x--" overload
// The compiler distinguishes between the pre-decrement operator and the
// post-decrement operator by having the post-decrement operator take an int type
// dummy argument.
Fixed Fixed::operator--(int) {
	Fixed tmp(*this);
	--*this;
	return tmp;
}

// \New!/ min(non-const, non-const) overload
// A static member function is not dependent on instances of the class and is shared
// among all instances of that class. (therefore, const qualifiers cannot be
// applied.)
Fixed &Fixed::min(Fixed &a, Fixed &b) {
	if (a < b) {
		return a;
	}
	return b;
}

// \New!/ min(const, const) overload
const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
	if (a < b) {
		return a;
	}
	return b;
}

// \New!/ max(non-const, non-const) overload
Fixed &Fixed::max(Fixed &a, Fixed &b) {
	if (a > b) {
		return a;
	}
	return b;
}
// \New!/ max(const, const) overload
const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
	if (a > b) {
		return a;
	}
	return b;
}

// destructor
Fixed::~Fixed() {
#ifndef NO_DEBUG
	std::cout << "Destructor called" << std::endl;
#endif
}

float Fixed::toFloat(void) const {
	return static_cast<float>(fixed_point_number_value_) /
		   (1 << kNumOfFractionalBits_);
}

int Fixed::toInt(void) const {
	return fixed_point_number_value_ / (1 << kNumOfFractionalBits_);
}

int Fixed::getRawBits(void) const {
	return fixed_point_number_value_;
}

void Fixed::setRawBits(const int raw) {
	fixed_point_number_value_ = raw;
}

// insertion operator overload
std::ostream &operator<<(std::ostream &out, const Fixed &f) {
	out << f.toFloat();
	return out;
}

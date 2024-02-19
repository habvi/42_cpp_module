#include "Fixed.hpp"
#include <cmath>
#include <iostream>

// default constructor
Fixed::Fixed() : fixed_point_number_value_(0) {}

// Int constructor
Fixed::Fixed(const int number)
	: fixed_point_number_value_(number << kNumOfFractionalBits_) {}

// Float constructor
Fixed::Fixed(const float number)
	: fixed_point_number_value_(
		  static_cast<int>(roundf(number * (1 << kNumOfFractionalBits_)))
	  ) {}

// copy constructor
Fixed::Fixed(const Fixed &f) : fixed_point_number_value_(f.getRawBits()) {}

// copy assignment operator overload
const Fixed &Fixed::operator=(const Fixed &f) {
	if (this != &f) {
		setRawBits(f.getRawBits());
	}
	return *this;
}

// comparison operator ">" overload
bool Fixed::operator>(const Fixed &f) const {
	return fixed_point_number_value_ > f.getRawBits();
}

// comparison operator "<" overload
bool Fixed::operator<(const Fixed &f) const {
	return fixed_point_number_value_ < f.getRawBits();
}

// comparison operator ">=" overload
bool Fixed::operator>=(const Fixed &f) const {
	return fixed_point_number_value_ >= f.getRawBits();
}

// comparison operator "<=" overload
bool Fixed::operator<=(const Fixed &f) const {
	return fixed_point_number_value_ <= f.getRawBits();
}

// comparison operator "==" overload
bool Fixed::operator==(const Fixed &f) const {
	return fixed_point_number_value_ == f.getRawBits();
}

// comparison operator "!=" overload
bool Fixed::operator!=(const Fixed &f) const {
	return fixed_point_number_value_ != f.getRawBits();
}

// arithmetic operator "+" overload
Fixed Fixed::operator+(const Fixed &f) const {
	Fixed tmp(*this);
	tmp += f;
	return tmp;
}

// arithmetic operator "-" overload
Fixed Fixed::operator-(const Fixed &f) const {
	Fixed tmp(*this);
	tmp -= f;
	return tmp;
}

// arithmetic operator "*" overload
Fixed Fixed::operator*(const Fixed &f) const {
	Fixed tmp(*this);
	tmp *= f;
	return tmp;
}

// arithmetic operator "/" overload
Fixed Fixed::operator/(const Fixed &f) const {
	Fixed tmp(*this);
	tmp /= f;
	return tmp;
}

// (not required) arithmetic operator "+=" overload
const Fixed &Fixed::operator+=(const Fixed &f) {
	fixed_point_number_value_ += f.getRawBits();
	return *this;
}

// (not required) arithmetic operator "-=" overload
const Fixed &Fixed::operator-=(const Fixed &f) {
	fixed_point_number_value_ -= f.getRawBits();
	return *this;
}

// (not required) arithmetic operator "*=" overload
const Fixed &Fixed::operator*=(const Fixed &f) {
	fixed_point_number_value_ =
		fixed_point_number_value_ * f.getRawBits() >> kNumOfFractionalBits_;
	return *this;
}

// (not required) arithmetic operator "/=" overload
const Fixed &Fixed::operator/=(const Fixed &f) {
	fixed_point_number_value_ = fixed_point_number_value_ / f.getRawBits()
								<< kNumOfFractionalBits_;
	return *this;
}

// pre-increment operator "++x" overload
const Fixed &Fixed::operator++() {
	fixed_point_number_value_++;
	return *this;
}

// post-increment operator "x++" overload
// The compiler distinguishes between the pre-increment operator and the
// post-increment operator by having the post-increment operator take an int type
// dummy argument.
Fixed Fixed::operator++(int) {
	Fixed tmp(*this);
	++*this;
	return tmp;
}

// pre-decrement operator "--x" overload
const Fixed &Fixed::operator--() {
	fixed_point_number_value_--;
	return *this;
}

// post-decrement operator "x--" overload
// The compiler distinguishes between the pre-decrement operator and the
// post-decrement operator by having the post-decrement operator take an int type
// dummy argument.
Fixed Fixed::operator--(int) {
	Fixed tmp(*this);
	--*this;
	return tmp;
}

// min(non-const, non-const) overload
// A static member function is not dependent on instances of the class and is shared
// among all instances of that class. (therefore, const qualifiers cannot be
// applied.)
Fixed &Fixed::min(Fixed &a, Fixed &b) {
	if (a < b) {
		return a;
	}
	return b;
}

// min(const, const) overload
const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
	if (a < b) {
		return a;
	}
	return b;
}

// max(non-const, non-const) overload
Fixed &Fixed::max(Fixed &a, Fixed &b) {
	if (a > b) {
		return a;
	}
	return b;
}
// max(const, const) overload
const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
	if (a > b) {
		return a;
	}
	return b;
}

// destructor
Fixed::~Fixed() {}

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

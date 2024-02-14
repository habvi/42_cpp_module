#include "Fixed.hpp"
#include <cmath>
#include <iostream>

// default constructor
Fixed::Fixed() : fixed_point_number_(0) {
	std::cout << "Default constructor called" << std::endl;
}

// \New!/ Int constructor
Fixed::Fixed(const int number)
	: fixed_point_number_(number << kNumOfFractionalBits_) {
	std::cout << "Int constructor called" << std::endl;
}

// \New!/ Float constructor
Fixed::Fixed(const float number)
	: fixed_point_number_(
		  static_cast<int>(roundf(number * (1 << kNumOfFractionalBits_)))
	  ) {
	std::cout << "Float constructor called" << std::endl;
}

// copy constructor
Fixed::Fixed(const Fixed &f) : fixed_point_number_(f.getRawBits()) {
	std::cout << "Copy constructor called" << std::endl;
}

// copy assignment operator overload
const Fixed &Fixed::operator=(const Fixed &f) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &f) {
		setRawBits(f.getRawBits());
	}
	return *this;
}

// destructor
Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

// \New!/
float Fixed::toFloat(void) const {
	return static_cast<float>(fixed_point_number_) / (1 << kNumOfFractionalBits_);
}

// \New!/
int Fixed::toInt(void) const {
	return fixed_point_number_ >> kNumOfFractionalBits_;
}

int Fixed::getRawBits(void) const {
	return fixed_point_number_;
}

void Fixed::setRawBits(const int raw) {
	fixed_point_number_ = raw;
}

// \New!/ insertion operator overload
std::ostream &operator<<(std::ostream &out, const Fixed &f) {
	out << f.toFloat();
	return out;
}

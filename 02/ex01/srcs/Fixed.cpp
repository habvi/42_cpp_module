#include "Fixed.hpp"
#include <iostream>

// default constructor
Fixed::Fixed() : fixed_point_number_(0) {
	std::cout << "Default constructor called" << std::endl;
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

int Fixed::getRawBits(void) const {
	return fixed_point_number_;
}

void Fixed::setRawBits(const int raw) {
	fixed_point_number_ = raw;
}


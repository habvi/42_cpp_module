#include "Fixed.hpp"
#include <iostream>

// default constructor
Fixed::Fixed() {
	std::cout << "Default constructor called" << std::endl;
	fixed_point_number_ = 0;
}

// copy constructor
Fixed::Fixed(const Fixed &f) {
	std::cout << "Copy constructor called" << std::endl;
	setRawBits(f.getRawBits());
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
	std::cout << "getRawBits member function called" << std::endl;
	return fixed_point_number_;
}

void Fixed::setRawBits(int const raw) {
	fixed_point_number_ = raw;
}

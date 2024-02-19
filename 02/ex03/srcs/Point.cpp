#include "Point.hpp"
#include "Fixed.hpp"

// default constructor
Point::Point() : x(0), y(0) {}

// constructor
Point::Point(const float floating_point_num_1, const float floating_point_num_2)
	: x(floating_point_num_1), y(floating_point_num_2) {}

// copy constructor
Point::Point(const Point &p) {
	*this = p;
}

// copy assignment operator overload
Point &Point::operator=(const Point &p) {
	if (this != &p) {
		const_cast<Fixed &>(x) = Fixed(p.getX());
		const_cast<Fixed &>(y) = Fixed(p.getY());
	}
	return *this;
}

const Fixed &Point::getX() const {
	return x;
}

const Fixed &Point::getY() const {
	return y;
}

// destructor
Point::~Point() {}

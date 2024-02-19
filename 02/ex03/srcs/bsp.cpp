#include "Point.hpp"

static const Fixed CrossProduct(Point const &a, Point const &b, Point const &c) {
	return (a.getX() - c.getX()) * (b.getY() - c.getY()) -
		   (b.getX() - c.getX()) * (a.getY() - c.getY());
}

// is point inside triangle(a, b, c);
bool bsp(Point const a, Point const b, Point const c, Point const point) {
	const Fixed zero;

	const Fixed result1 = CrossProduct(point, a, b);
	const Fixed result2 = CrossProduct(point, b, c);
	const Fixed result3 = CrossProduct(point, c, a);
	return (
		(result1 > zero && result2 > zero && result3 > zero) ||
		(result1 < zero && result2 < zero && result3 < zero)
	);
}

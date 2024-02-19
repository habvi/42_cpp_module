#ifndef POINT_H
#define POINT_H

#include "Fixed.hpp"

class Point {
  public:
	Point();
	Point(const float floating_point_num_1, const float floating_point_num_2);
	Point(const Point &p);
	Point &operator=(const Point &p);
	~Point();

  public:
	const Fixed &getX() const;
	const Fixed &getY() const;

  private:
	// Following the instructions, underscore is not used.
	const Fixed x;
	const Fixed y;
};

bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif /* POINT_H */

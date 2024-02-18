#ifndef FIXED_H
#define FIXED_H

#include <ostream>

class Fixed {
  public:
	Fixed();
	Fixed(const int number);
	Fixed(const float number);
	Fixed(const Fixed &f);
	const Fixed &operator=(const Fixed &f);
	Fixed        operator+(const Fixed &f) const;
	Fixed        operator-(const Fixed &f) const;
	Fixed        operator*(const Fixed &f) const;
	Fixed        operator/(const Fixed &f) const;
	Fixed        operator+=(const Fixed &f);
	Fixed        operator-=(const Fixed &f);
	Fixed        operator*=(const Fixed &f);
	Fixed        operator/=(const Fixed &f);
	~Fixed();

  public:
	// Following the instructions, not camelcase.
	float toFloat(void) const;
	int   toInt(void) const;
	int   getRawBits(void) const;
	void  setRawBits(const int raw);

  private:
	int              fixed_point_number_value_;
	static const int kNumOfFractionalBits_ = 8;
};

std::ostream &operator<<(std::ostream &out, const Fixed &f);

#endif /* FIXED_H */

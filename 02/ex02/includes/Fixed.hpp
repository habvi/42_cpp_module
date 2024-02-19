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
	~Fixed();

	bool operator>(const Fixed &f) const;
	bool operator<(const Fixed &f) const;
	bool operator>=(const Fixed &f) const;
	bool operator<=(const Fixed &f) const;
	bool operator==(const Fixed &f) const;
	bool operator!=(const Fixed &f) const;

	Fixed        operator+(const Fixed &f) const;
	Fixed        operator-(const Fixed &f) const;
	Fixed        operator*(const Fixed &f) const;
	Fixed        operator/(const Fixed &f) const;
	const Fixed &operator+=(const Fixed &f);
	const Fixed &operator-=(const Fixed &f);
	const Fixed &operator*=(const Fixed &f);
	const Fixed &operator/=(const Fixed &f);

	const Fixed &operator++();
	Fixed        operator++(int);
	const Fixed &operator--();
	Fixed        operator--(int);

	static Fixed       &min(Fixed &a, Fixed &b);
	static const Fixed &min(const Fixed &a, const Fixed &b);
	static Fixed       &max(Fixed &a, Fixed &b);
	static const Fixed &max(const Fixed &a, const Fixed &b);

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

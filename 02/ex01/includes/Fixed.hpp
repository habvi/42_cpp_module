#ifndef FIXED_H
#define FIXED_H

class Fixed {
  public:
	Fixed();
	Fixed(const int number);
	Fixed(const float number);
	Fixed(const Fixed &f);
	const Fixed &operator=(const Fixed &f);
	~Fixed();

  public:
	// Following the instructions, not camelcase.
	float toFloat(void) const;
	int   toInt(void) const;
	int   getRawBits(void) const;
	void  setRawBits(const int raw);

  private:
	int              fixed_point_number_;
	static const int kNumOfFractionalBits_ = 8;
};

#endif /* FIXED_H */

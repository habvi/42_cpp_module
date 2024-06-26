#ifndef FIXED_H
#define FIXED_H

class Fixed {
  public:
	Fixed();
	Fixed(const Fixed &f);
	Fixed &operator=(const Fixed &f);
	~Fixed();

  public:
	// Following the instructions, not camelcase.
	int  getRawBits(void) const;
	void setRawBits(int const raw);

  private:
	int              fixed_point_number_value_;
	static const int kNumOfFractionalBits_ = 8;
};

#endif /* FIXED_H */

#ifndef EX02_CLOCK_HPP
#define EX02_CLOCK_HPP

#include <time.h>

class Clock {
  public:
	Clock();
	~Clock();

  private:
	Clock(const Clock &other);
	Clock &operator=(const Clock &other);
	// variables
	struct timespec start_;
	struct timespec end_;
};

#endif /* EX02_CLOCK_HPP */

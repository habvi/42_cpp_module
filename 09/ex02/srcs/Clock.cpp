#include "Clock.hpp"
#include <iostream>

Clock::Clock() {
	clock_gettime(CLOCK_REALTIME, &start_);
}

Clock::~Clock() {
	clock_gettime(CLOCK_REALTIME, &end_);
	const double spent_time = (end_.tv_sec - start_.tv_sec) * 1000000 +
							  (end_.tv_nsec - start_.tv_nsec) / 1000;
	std::cout << spent_time << " us" << std::endl;
}

Clock::Clock(const Clock &other) : start_(other.start_), end_(other.end_) {}

Clock &Clock::operator=(const Clock &other) {
	if (this != &other) {
		start_ = other.start_;
		end_   = other.end_;
	}
	return *this;
}

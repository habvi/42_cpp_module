#ifndef EX00_UTILS_HPP
#define EX00_UTILS_HPP

#include <limits>

template <typename T, typename U>
bool IsSame(const T &before, const U &after) {
	return before == after;
}

template <typename T>
bool IsNan(const T &num) {
	return num != num;
}

template <typename T>
bool IsInfinity(const T &num) {
	static const double inf = std::numeric_limits<double>::infinity();
	return num == inf || num == -inf;
}

template <typename T>
bool IsInfinityOrNan(const T &num) {
	return IsInfinity(num) || IsNan(num);
}

#endif /* EX00_UTILS_HPP */

#ifndef EX01_ITER_HPP
#define EX01_ITER_HPP

#include <cstddef>

template <typename T>
void iter(T *array, const size_t length, void (*func)(T &)) {
	if (!array || !func) {
		return;
	}
	for (size_t i = 0; i < length; i++) {
		func(array[i]);
	}
}

template <typename T>
void iter(const T *array, const size_t length, void (*func)(const T &)) {
	if (!array || !func) {
		return;
	}
	for (size_t i = 0; i < length; i++) {
		func(array[i]);
	}
}

#endif /* EX01_ITER_HPP */

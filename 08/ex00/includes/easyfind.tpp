#include <algorithm>

// If the value is not found, returns the container's end iterator.
template <typename T>
typename T::const_iterator easyfind(const T &container, const int value) {
	typename T::const_iterator begin = container.begin();
	typename T::const_iterator end   = container.end();
	typename T::const_iterator itr   = std::find(begin, end, value);

	return itr;
}

// If the value is not found, returns the container's end iterator.
template <typename T>
typename T::iterator easyfind(T &container, const int value) {
	typename T::iterator begin = container.begin();
	typename T::iterator end   = container.end();
	typename T::iterator itr   = std::find(begin, end, value);

	return itr;
}

#ifndef EX00_EASYFIND_HPP
#define EX00_EASYFIND_HPP

template <typename T>
typename T::const_iterator easyfind(const T &container, const int &value);
template <typename T>
typename T::iterator easyfind(T &container, const int &value);

#include "easyfind.tpp"

#endif /* EX00_EASYFIND_HPP */

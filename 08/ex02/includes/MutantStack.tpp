#include "color.hpp"
#include <iostream>

template <typename T>
MutantStack<T>::MutantStack() {}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &other)
	: std::stack< T, std::deque<T> >(other) {}

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack &other) {
	if (this != &other) {
		std::stack<T>::operator=(other);
	}
	return *this;
}

template <typename T>
MutantStack<T>::~MutantStack() {}

// ---------------------------------------------------
template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
	return std::stack<T>::c.begin();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin() const {
	return std::stack<T>::c.begin();
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() {
	return std::stack<T>::c.end();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end() const {
	return std::stack<T>::c.end();
}

template <typename T>
std::size_t MutantStack<T>::size() const {
	return std::stack<T>::size();
}

// ---------------------------------------------------
// debug
// ---------------------------------------------------
template <typename T>
void MutantStack<T>::DebugPrint() {
	std::cout << COLOR_PINK "mstack" COLOR_END " (size:" << size() << ")"
			  << std::endl;
	std::cout << "==> {";
	typename std::deque<T>::iterator itr;
	for (itr = begin(); itr != end(); ++itr) {
		if (itr != begin()) {
			std::cout << ", ";
		}
		std::cout << *itr;
	}
	std::cout << "}" << std::endl;
}

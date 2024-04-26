#include "color.hpp"
#include <iostream>

template <typename T>
MutantStack<T>::MutantStack() {}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &other)
	: std::stack< T, Container >(other) {}

// Preventing self-assignment is delegated to the parent class.
template <typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack &other) {
	std::stack<T>::operator=(other);
	return *this;
}

template <typename T>
MutantStack<T>::~MutantStack() {}

// ---------------------------------------------------
template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
	return this->c.begin();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin() const {
	return this->c.begin();
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() {
	return this->c.end();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end() const {
	return this->c.end();
}

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rbegin() {
	return this->c.rbegin();
}

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rbegin() const {
	return this->c.rbegin();
}

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rend() {
	return this->c.rend();
}

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rend() const {
	return this->c.rend();
}

// ---------------------------------------------------
// debug
// ---------------------------------------------------
template <typename T>
std::ostream &MutantStack<T>::Print(std::ostream &out) const {
	out << COLOR_PINK "mstack" COLOR_END " (size:" << this->size() << ")"
		<< std::endl;
	out << "==> {";
	const_iterator itr;
	for (itr = begin(); itr != end(); ++itr) {
		if (itr != begin()) {
			out << ", ";
		}
		out << *itr;
	}
	out << "}" << std::endl;
	return out;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const MutantStack<T> &m) {
	return m.Print(out);
}

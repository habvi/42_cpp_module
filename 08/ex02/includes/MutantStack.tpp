#include "color.hpp"
#include <iostream>

template <typename T, typename Container>
MutantStack<T, Container>::MutantStack() {}

template <typename T, typename Container>
MutantStack<T, Container>::MutantStack(const MutantStack &other)
	: std::stack< T, Container >(other) {}

// Preventing self-assignment is delegated to the parent class.
template <typename T, typename Container>
MutantStack<T, Container> &
MutantStack<T, Container>::operator=(const MutantStack &other) {
	std::stack<T>::operator=(other);
	return *this;
}

template <typename T, typename Container>
MutantStack<T, Container>::~MutantStack() {}

// ---------------------------------------------------
template <typename T, typename Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::begin() {
	return this->c.begin();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_iterator
MutantStack<T, Container>::begin() const {
	return this->c.begin();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::iterator MutantStack<T, Container>::end() {
	return this->c.end();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_iterator
MutantStack<T, Container>::end() const {
	return this->c.end();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::reverse_iterator
MutantStack<T, Container>::rbegin() {
	return this->c.rbegin();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_reverse_iterator
MutantStack<T, Container>::rbegin() const {
	return this->c.rbegin();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::reverse_iterator
MutantStack<T, Container>::rend() {
	return this->c.rend();
}

template <typename T, typename Container>
typename MutantStack<T, Container>::const_reverse_iterator
MutantStack<T, Container>::rend() const {
	return this->c.rend();
}

// ---------------------------------------------------
// debug
// ---------------------------------------------------
template <typename T, typename Container>
std::ostream &MutantStack<T, Container>::Print(std::ostream &out) const {
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
	out << "}";
	return out;
}

template <typename T, typename Container>
std::ostream &operator<<(std::ostream &out, const MutantStack<T, Container> &m) {
	return m.Print(out);
}

#include "Span.hpp"

Span::Span() : max_elem_size_(0) {}

Span::Span(const unsigned int n) : max_elem_size_(n) {}

Span::Span(const Span &other) : max_elem_size_(other.max_elem_size_) {
	// todo Deepcopy
	(void)other;
}

const Span &Span::operator=(const Span &other) {
	if (this != &other) {
		// todo Deepcopy
	}
	(void)other;
	return *this;
}

Span::~Span() {}

// ---------------------------------------------------
void Span::addNumber(const unsigned int number) {
	orderd_elems_[number]++;
}

unsigned int Span::shortestSpan() const {
	return 1;
}

unsigned int Span::longestSpan() const {
	return 1;
}

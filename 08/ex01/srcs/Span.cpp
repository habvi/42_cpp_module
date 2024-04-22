#include "Span.hpp"
#include <iostream>
#include <stdexcept>

Span::Span() : max_elem_size_(0), elem_count_(0) {}

Span::Span(const unsigned int n) : max_elem_size_(n), elem_count_(0) {}

Span::Span(const Span &other)
	: max_elem_size_(other.max_elem_size_), elem_count_(other.elem_count_) {
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
	if (elem_count_ == max_elem_size_) {
		throw std::runtime_error("Span is full");
	}
	orderd_elems_[number]++;
	elem_count_++;
	putStoredNumbers();
}

unsigned int Span::shortestSpan() const {
	return 1;
}

unsigned int Span::longestSpan() const {
	return 1;
}

// ---------------------------------------------------
void Span::putStoredNumbers() const {
	std::cout << "map (size:" << orderd_elems_.size() << ") : {";
	MapElems::const_iterator itr;
	for (itr = orderd_elems_.begin(); itr != orderd_elems_.end(); ++itr) {
		if (itr != orderd_elems_.begin()) {
			std::cout << ", ";
		}
		std::cout << "{" << itr->first << ", " << itr->second << "}";
	}
	std::cout << "}" << std::endl;
	std::cout << "--------------" << std::endl;
}

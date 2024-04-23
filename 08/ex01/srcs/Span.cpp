#include "Span.hpp"
#include <climits>
#include <iostream>
#include <stdexcept>

Span::Span() : max_elem_size_(0), elem_count_(0), shortest_span_(UINT_MAX) {}

Span::Span(const unsigned int n)
	: max_elem_size_(n), elem_count_(0), shortest_span_(UINT_MAX) {}

Span::Span(const Span &other)
	: max_elem_size_(other.max_elem_size_),
	  elem_count_(other.elem_count_),
	  shortest_span_(other.shortest_span_) {
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
	updateShortestSpan(number);
	orderd_elems_[number]++;
	elem_count_++;
	putStoredNumbers();
}

void Span::throwExceptionIfLessElemCounts() const {
	if (elem_count_ == 0 || elem_count_ == 1) {
		throw std::runtime_error("Span elements needs more than 2");
	}
}

unsigned int Span::shortestSpan() const {
	throwExceptionIfLessElemCounts();
	return shortest_span_;
}

unsigned int Span::longestSpan() const {
	throwExceptionIfLessElemCounts();
	return 1;
}

// ---------------------------------------------------
void Span::updateShortestSpanMember(const unsigned int &new_span) {
	if (new_span < shortest_span_) {
		shortest_span_ = new_span;
	}
}

void Span::updateShortestSpan(const unsigned int &number) {
	// empty
	if (orderd_elems_.empty()) {
		return;
	}
	// same element
	if (orderd_elems_.count(number) > 0) {
		shortest_span_ = 0;
		return;
	}
	// new element
	MapElems::const_iterator itr = orderd_elems_.lower_bound(number);
	if (itr != orderd_elems_.begin()) {
		// always exist lower element
		--itr;
		updateShortestSpanMember(number - itr->first);
	}
	if (itr != orderd_elems_.end()) {
		// always exist higher element
		updateShortestSpanMember(itr->first - number);
	}
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

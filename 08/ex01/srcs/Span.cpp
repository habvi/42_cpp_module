#include "Span.hpp"
#include <climits>
#include <iostream>
#include <stdexcept>

Span::Span()
	: max_elem_size_(0),
	  elem_count_(0),
	  shortest_span_(UINT_MAX),
	  longest_span_(0) {}

Span::Span(const unsigned int n)
	: max_elem_size_(n),
	  elem_count_(0),
	  shortest_span_(UINT_MAX),
	  longest_span_(0) {}

Span::Span(const Span &other)
	: max_elem_size_(other.max_elem_size_),
	  elem_count_(other.elem_count_),
	  orderd_elems_(other.orderd_elems_),
	  shortest_span_(other.shortest_span_),
	  longest_span_(other.longest_span_) {}

const Span &Span::operator=(const Span &other) {
	if (this != &other) {
		elem_count_    = other.elem_count_;
		orderd_elems_  = other.orderd_elems_;
		shortest_span_ = other.shortest_span_;
		longest_span_  = other.longest_span_;
	}
	return *this;
}

Span::~Span() {}

// ---------------------------------------------------
void Span::addNumber(const unsigned int number) {
	if (elem_count_ == max_elem_size_) {
		throw std::runtime_error("Span is full");
	}
	UpdateShortestSpan(number);
	orderd_elems_[number]++;
	elem_count_++;
	UpdateLongestSpan();
}

void Span::ThrowExceptionIfLessElemCounts() const {
	if (elem_count_ == 0 || elem_count_ == 1) {
		throw std::runtime_error("Span elements needs more than 2");
	}
}

unsigned int Span::shortestSpan() const {
	ThrowExceptionIfLessElemCounts();
	return shortest_span_;
}

unsigned int Span::longestSpan() const {
	ThrowExceptionIfLessElemCounts();
	return longest_span_;
}

void Span::Insert(const unsigned int count, const unsigned int value) {
	for (size_t i = 0; i < count; i++) {
		addNumber(value);
	}
}

// ---------------------------------------------------
void Span::UpdateShortestSpanMember(const unsigned int &new_span) {
	if (new_span < shortest_span_) {
		shortest_span_ = new_span;
	}
}

void Span::UpdateLongestSpanMember(const unsigned int &new_span) {
	if (new_span > longest_span_) {
		longest_span_ = new_span;
	}
}

void Span::UpdateShortestSpan(const unsigned int &number) {
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
		UpdateShortestSpanMember(number - itr->first);
	}
	if (itr != orderd_elems_.end()) {
		// always exist higher element
		UpdateShortestSpanMember(itr->first - number);
	}
}

// at least one element exist
void Span::UpdateLongestSpan() {
	if (orderd_elems_.size() < 2) {
		return;
	}
	MapElems::const_iterator begin = orderd_elems_.begin();
	MapElems::const_iterator end   = orderd_elems_.end();
	// always exist lower element
	--end;
	const unsigned int span = end->first - begin->first;
	UpdateLongestSpanMember(span);
}

// ---------------------------------------------------
unsigned int Span::max_elem_size() const {
	return max_elem_size_;
}

unsigned int Span::elem_count() const {
	return elem_count_;
}

const Span::MapElems &Span::orderd_elems() const {
	return orderd_elems_;
}

unsigned int Span::shortest_span() const {
	return shortest_span_;
}

unsigned int Span::longest_span() const {
	return longest_span_;
}

// ---------------------------------------------------
// debug
// ---------------------------------------------------
void Span::PutElems() const {
	std::cout << "map (size:" << orderd_elems_.size()
			  << "),(elem count:" << elem_count_ << ")" << std::endl;
	std::cout << "==> {";
	MapElems::const_iterator itr;
	for (itr = orderd_elems_.begin(); itr != orderd_elems_.end(); ++itr) {
		if (itr != orderd_elems_.begin()) {
			std::cout << ", ";
		}
		std::cout << "{" << itr->first << ", " << itr->second << "}";
	}
	std::cout << "}" << std::endl;
}

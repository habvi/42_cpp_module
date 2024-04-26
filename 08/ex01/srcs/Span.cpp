#include "Span.hpp"
#include <climits>
#include <iostream>
#include <stdexcept>

Span::Span() : capacity_(0), size_(0), shortest_span_(UINT_MAX), longest_span_(0) {}

Span::Span(const unsigned int n)
	: capacity_(n), size_(0), shortest_span_(UINT_MAX), longest_span_(0) {}

Span::Span(const Span &other)
	: capacity_(other.capacity_),
	  size_(other.size_),
	  orderd_elems_(other.orderd_elems_),
	  shortest_span_(other.shortest_span_),
	  longest_span_(other.longest_span_) {}

const Span &Span::operator=(const Span &other) {
	if (this != &other) {
		capacity_      = other.capacity_;
		size_          = other.size_;
		orderd_elems_  = other.orderd_elems_;
		shortest_span_ = other.shortest_span_;
		longest_span_  = other.longest_span_;
	}
	return *this;
}

Span::~Span() {}

// ---------------------------------------------------
void Span::addNumber(const unsigned int number) {
	if (size_ >= capacity_) {
		throw std::logic_error("Span is full");
	}
	InsertResult result = orderd_elems_.insert(number);
	size_++;
	UpdateShortestSpan(result);
	UpdateLongestSpan();
}

static void ThrowExceptionIfLessElemCounts(const std::size_t size) {
	if (size < 2) {
		throw std::logic_error("Span needs at least 2 elements");
	}
}

unsigned int Span::shortestSpan() const {
	ThrowExceptionIfLessElemCounts(size_);
	return shortest_span_;
}

unsigned int Span::longestSpan() const {
	ThrowExceptionIfLessElemCounts(size_);
	return longest_span_;
}

// addNumber: start ~ (end - 1)
// if start >= end, nothing happend.
void Span::Insert(const unsigned int start, const unsigned int end) {
	for (unsigned int i = start; i < end; i++) {
		addNumber(i);
	}
}

// ---------------------------------------------------
void Span::UpdateShortestSpan(InsertResult result) {
	const bool is_new_number = result.second;
	if (!is_new_number) {
		shortest_span_ = 0;
		return;
	}
	// new element (lower_bound)
	Elems::const_iterator lower  = result.first;
	Elems::const_iterator higher = result.first;
	if (higher != orderd_elems_.begin()) {
		// always exist lower element
		shortest_span_ = std::min(shortest_span_, *higher - *(--lower));
		++lower;
	}
	if (lower != --orderd_elems_.end()) {
		// always exist higher element
		shortest_span_ = std::min(shortest_span_, *(++higher) - *lower);
		--higher;
	}
}

// at least one element exist
void Span::UpdateLongestSpan() {
	if (orderd_elems_.size() < 2) {
		return;
	}
	Elems::const_iterator begin = orderd_elems_.begin();
	Elems::const_iterator end   = orderd_elems_.end();
	// always exist lower element
	--end;
	longest_span_ = std::max(longest_span_, *end - *begin);
}

// ---------------------------------------------------
bool Span::IsSameSpan(const Span &other) const {
	if (this == &other) {
		return true;
	}
	// Elems
	const Span::Elems elems1 = orderd_elems_;
	const Span::Elems elems2 = other.orderd_elems_;
	if (elems1.size() != elems2.size()) {
		return false;
	}
	Elems::const_iterator itr1 = elems1.begin();
	Elems::const_iterator itr2 = elems2.begin();
	for (; itr1 != elems1.end(); ++itr1) {
		if (*itr1 != *itr2) {
			return false;
		}
		++itr2;
	}
	// other members
	if (capacity_ != other.capacity_ || size_ != other.size_ ||
		shortest_span_ != other.shortest_span_ ||
		longest_span_ != other.longest_span_) {
		return false;
	}
	return true;
}

// ---------------------------------------------------
// debug
// ---------------------------------------------------
void Span::PutElems() const {
	std::cout << "Elems (size:" << orderd_elems_.size() << ")" << std::endl;
	std::cout << "==> {";
	Elems::const_iterator itr;
	for (itr = orderd_elems_.begin(); itr != orderd_elems_.end(); ++itr) {
		if (itr != orderd_elems_.begin()) {
			std::cout << ", ";
		}
		std::cout << *itr;
	}
	std::cout << "}" << std::endl;
}

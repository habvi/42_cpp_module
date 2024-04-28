#include "Span.hpp"
#include <climits>
#include <stdexcept>

const std::string Span::kErrMsgNotEnoughSize = "Not enough elements size";
const std::string Span::kErrMsgFullCapacity  = "Capacity is full";

Span::Span() : capacity_(0), size_(0), shortest_span_(UINT_MAX), longest_span_(0) {}

Span::Span(const unsigned int n)
	: capacity_(n), size_(0), shortest_span_(UINT_MAX), longest_span_(0) {}

Span::Span(const Span &other)
	: capacity_(other.capacity_),
	  size_(other.size_),
	  orderd_elems_(other.orderd_elems_),
	  shortest_span_(other.shortest_span_),
	  longest_span_(other.longest_span_) {}

Span &Span::operator=(const Span &other) {
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
void Span::addNumber(const int number) {
	if (size_ >= capacity_) {
		throw std::logic_error(kErrMsgFullCapacity);
	}
	InsertResult result = orderd_elems_.insert(number);
	size_++;
	UpdateShortestSpan(result);
	UpdateLongestSpan();
}

unsigned int Span::shortestSpan() const {
	if (size_ < 2) {
		throw std::logic_error(kErrMsgNotEnoughSize);
	}
	return shortest_span_;
}

unsigned int Span::longestSpan() const {
	if (size_ < 2) {
		throw std::logic_error(kErrMsgNotEnoughSize);
	}
	return longest_span_;
}

// addNumber: start ~ (end - 1)
// if start >= end, nothing happend.
void Span::Insert(const int start, const int end) {
	for (int i = start; i < end; i++) {
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
	// new number (lower_bound)
	const Elems::const_iterator pos = result.first;
	if (pos != orderd_elems_.begin()) {
		// always exist lower element
		const Elems::const_iterator prev = --Elems::iterator(pos);
		const unsigned int          span = static_cast<unsigned int>(*pos - *prev);
		shortest_span_                   = std::min(shortest_span_, span);
	}
	if (pos != --orderd_elems_.end()) {
		// always exist higher element
		const Elems::const_iterator next = ++Elems::iterator(pos);
		const unsigned int          span = static_cast<unsigned int>(*next - *pos);
		shortest_span_                   = std::min(shortest_span_, span);
	}
}

// at least one element exist
void Span::UpdateLongestSpan() {
	if (orderd_elems_.size() < 2) {
		return;
	}
	const Elems::const_iterator first = orderd_elems_.begin();
	// always exist lower element
	const Elems::const_iterator last = --orderd_elems_.end();
	const unsigned int          span = static_cast<unsigned int>(*last - *first);
	longest_span_                    = std::max(longest_span_, span);
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
std::ostream &Span::Print(std::ostream &out) const {
	out << "Elems (key kind: " << orderd_elems_.size() << ", size:" << size_
		<< ", shortest: " << shortest_span_ << ", longest: " << longest_span_ << ")"
		<< std::endl;
	out << "==> {";
	Elems::const_iterator itr;
	for (itr = orderd_elems_.begin(); itr != orderd_elems_.end(); ++itr) {
		if (itr != orderd_elems_.begin()) {
			out << ", ";
		}
		out << *itr;
	}
	out << "}" << std::endl;
	return out;
}

std::ostream &operator<<(std::ostream &out, const Span &s) {
	return s.Print(out);
}

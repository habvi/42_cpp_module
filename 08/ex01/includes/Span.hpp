#ifndef EX01_SPAN_HPP
#define EX01_SPAN_HPP

#include <ostream>
#include <set>

class Span {
  public:
	typedef std::set<int>                          Elems;
	typedef std::pair<Elems::const_iterator, bool> InsertResult;

  public:
	Span(const unsigned int n);
	Span(const Span &other);
	Span &operator=(const Span &other);
	~Span();

  public:
	// Following the instructions, not camelcase.
	void         addNumber(const int number);
	unsigned int shortestSpan() const;
	unsigned int longestSpan() const;
	// original functions
	void Insert(const int start, const int end);
	template <typename T>
	void Insert(typename T::const_iterator first, typename T::const_iterator last);
	std::ostream &Print(std::ostream &out) const;
	bool          IsSameSpan(const Span &other) const;

  private:
	Span();
	void UpdateShortestSpan(InsertResult result);
	void UpdateLongestSpan();

  private:
	static const std::string kErrMsgNotEnoughSize;
	static const std::string kErrMsgFullCapacity;
	unsigned int             capacity_;
	unsigned int             size_;
	Elems                    orderd_elems_;
	unsigned int             shortest_span_;
	unsigned int             longest_span_;
};

template <typename T>
void Span::Insert(
	typename T::const_iterator first, typename T::const_iterator last
) {
	for (; first != last; ++first) {
		addNumber(*first);
	}
}

std::ostream &operator<<(std::ostream &out, const Span &s);

#endif /* EX01_SPAN_HPP */

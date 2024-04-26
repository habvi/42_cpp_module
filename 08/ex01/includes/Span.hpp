#ifndef EX01_SPAN_HPP
#define EX01_SPAN_HPP

#include <set>

class Span {
  public:
	typedef std::set<unsigned int>                 Elems;
	typedef std::pair<Elems::const_iterator, bool> InsertResult;

  public:
	Span(const unsigned int n);
	Span(const Span &other);
	const Span &operator=(const Span &other);
	~Span();

  public:
	// Following the instructions, not camelcase.
	void         addNumber(const unsigned int number);
	unsigned int shortestSpan() const;
	unsigned int longestSpan() const;
	void         Insert(const unsigned int start, const unsigned int end);
	template <typename T>
	void Insert(typename T::const_iterator first, typename T::const_iterator last);
	void PutElems() const;

  public:
	// getter for test
	unsigned int capacity() const;
	const Elems &orderd_elems() const;
	unsigned int shortest_span() const;
	unsigned int longest_span() const;

  private:
	Span();
	void UpdateShortestSpan(InsertResult result);
	void UpdateLongestSpan();

  private:
	unsigned int capacity_;
	unsigned int size_;
	Elems        orderd_elems_;
	unsigned int shortest_span_;
	unsigned int longest_span_;
};

template <typename T>
void Span::Insert(
	typename T::const_iterator first, typename T::const_iterator last
) {
	for (; first != last; ++first) {
		addNumber(*first);
	}
}

#endif /* EX01_SPAN_HPP */

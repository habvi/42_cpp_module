#ifndef EX01_SPAN_HPP
#define EX01_SPAN_HPP

#include <map>

class Span {
  public:
	typedef std::map<unsigned int, unsigned int> MapElems;

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
	void         Insert(const unsigned int count, const unsigned int value);
	template <typename T>
	void Insert(typename T::const_iterator first, typename T::const_iterator last);
	void PutStoredNumbers() const;

  public:
	// getter for test
	unsigned int    max_elem_size() const;
	unsigned int    elem_count() const;
	const MapElems &orderd_elems() const;
	unsigned int    shortest_span() const;
	unsigned int    longest_span() const;

  private:
	Span();
	void ThrowExceptionIfLessElemCounts() const;
	void UpdateShortestSpan(const unsigned int &new_span);
	void UpdateShortestSpanMember(const unsigned int &new_span);
	void UpdateLongestSpan();
	void UpdateLongestSpanMember(const unsigned int &new_span);

  private:
	const unsigned int max_elem_size_;
	unsigned int       elem_count_;
	MapElems           orderd_elems_;
	unsigned int       shortest_span_;
	unsigned int       longest_span_;
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

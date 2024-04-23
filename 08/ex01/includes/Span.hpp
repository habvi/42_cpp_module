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
	void         addNumber(const unsigned int number);
	unsigned int shortestSpan() const;
	unsigned int longestSpan() const;

  private:
	Span();
	void updateShortestSpan(const unsigned int &new_span);
	void updateShortestSpanMember(const unsigned int &new_span);
	void updateLongestSpan();
	void updateLongestSpanMember(const unsigned int &new_span);
	void putStoredNumbers() const;
	void throwExceptionIfLessElemCounts() const;

  private:
	const unsigned int max_elem_size_;
	unsigned int       elem_count_;
	MapElems           orderd_elems_;
	unsigned int       shortest_span_;
	unsigned int       longest_span_;
};

#endif /* EX01_SPAN_HPP */

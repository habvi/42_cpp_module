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
	void putStoredNumbers() const;
	void throwExceptionIfLessElemCounts() const;

  private:
	const unsigned int max_elem_size_;
	unsigned int       elem_count_;
	MapElems           orderd_elems_;
};

#endif /* EX01_SPAN_HPP */

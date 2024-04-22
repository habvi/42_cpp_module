#ifndef EX01_SPAN_HPP
#define EX01_SPAN_HPP

class Span {
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

  private:
	const unsigned int max_elem_size_;
};

#endif /* EX01_SPAN_HPP */

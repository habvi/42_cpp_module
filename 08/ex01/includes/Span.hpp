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

  public:
	// getter for test
	unsigned int    max_elem_size() const;
	unsigned int    elem_count() const;
	const MapElems &orderd_elems() const;
	unsigned int    shortest_span() const;
	unsigned int    longest_span() const;

  private:
	Span();
	void deepcopyMembers(const Span &other);
	void throwExceptionIfLessElemCounts() const;
	void updateShortestSpan(const unsigned int &new_span);
	void updateShortestSpanMember(const unsigned int &new_span);
	void updateLongestSpan();
	void updateLongestSpanMember(const unsigned int &new_span);
	void putStoredNumbers() const;

  private:
	const unsigned int max_elem_size_;
	unsigned int       elem_count_;
	MapElems           orderd_elems_;
	unsigned int       shortest_span_;
	unsigned int       longest_span_;
};

#endif /* EX01_SPAN_HPP */

#ifndef EX02_ARRAY_HPP
#define EX02_ARRAY_HPP

#include <cstddef>

template <typename T>
class Array {
  public:
	Array();
	Array(unsigned int n);
	Array(const Array &other);
	~Array();
	Array &operator=(const Array &other);
	// for read : [i]
	const T &operator[](std::size_t index) const;
	// for write : [i] = x
	T &operator[](std::size_t index);

  public:
	// Following the instructions, not camelcase.
	unsigned int size() const;

  private:
	T   *DupArray(const Array &other);
	void ThrowIfIndexOutOfRange(std::size_t index) const;

  private:
	T           *array_;
	unsigned int size_;
};

#include "Array.tpp"

#endif /* EX02_ARRAY_HPP */

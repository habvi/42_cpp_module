#ifndef EX02_ARRAY_HPP
#define EX02_ARRAY_HPP

template <typename T>
class Array {
  public:
	Array();
	Array(const unsigned int n);
	Array(const Array &other);
	~Array();
	const Array &operator=(const Array &other);
	// for read : [i]
	const T &operator[](const unsigned int index) const;
	// for write : [i] = x
	T &operator[](const unsigned int index);

  public:
	unsigned int size() const;

  private:
	Array &Deepcopy(const Array &other);
	void   ThrowIfIndexOutOfRange(const unsigned int index) const;

  private:
	T           *array_;
	unsigned int size_;
};

#include "Array.tpp"

#endif /* EX02_ARRAY_HPP */

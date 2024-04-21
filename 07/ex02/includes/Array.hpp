#ifndef EX02_ARRAY_HPP
#define EX02_ARRAY_HPP

#include <stdexcept>

template <typename T>
class Array {
  public:
	Array() : array_(NULL){};
	Array(const unsigned int n) : array_(new T[n]), size_(n){};
	Array(const Array &other) {
		*this = Deepcopy(other);
	};
	~Array() {
		delete[] array_;
	};
	const Array &operator=(const Array &other) {
		if (this != &other) {
			delete[] array_;
			*this = Deepcopy(other);
		}
		return *this;
	};
	// for read : [i]
	const T &operator[](const unsigned int index) const {
		ThrowIfIndexOutOfRange(index);
		return array_[index];
	};
	// for write : [i] = x
	T &operator[](const unsigned int index) {
		ThrowIfIndexOutOfRange(index);
		return array_[index];
	};

  public:
	unsigned int size() const {
		return size_;
	};

  private:
	Array &Deepcopy(const Array &other) {
		size_  = other.size();
		array_ = new T[size_];
		for (unsigned int i = 0; i < size_; i++) {
			array_[i] = other[i];
		}
		return *this;
	}
	void ThrowIfIndexOutOfRange(const unsigned int index) const {
		if (index >= size_) {
			throw std::out_of_range("index out of bounds");
		}
	}

  private:
	T           *array_;
	unsigned int size_;
};

// #include "Array.tpp"

#endif /* EX02_ARRAY_HPP */

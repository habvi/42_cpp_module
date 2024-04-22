#include <stdexcept>

template <typename T>
Array<T>::Array() : array_(NULL), size_(0) {}

template <typename T>
Array<T>::Array(const unsigned int n) : array_(new T[n]), size_(n) {}

template <typename T>
Array<T>::Array(const Array &other) {
	DeepcopyMembers(other);
}

template <typename T>
Array<T>::~Array() {
	delete[] array_;
}

template <typename T>
const Array<T> &Array<T>::operator=(const Array &other) {
	if (this != &other) {
		delete[] array_;
		DeepcopyMembers(other);
	}
	return *this;
}

template <typename T>
const T &Array<T>::operator[](const unsigned int index) const {
	ThrowIfIndexOutOfRange(index);
	return array_[index];
}

template <typename T>
T &Array<T>::operator[](const unsigned int index) {
	ThrowIfIndexOutOfRange(index);
	return array_[index];
}

// --------------------------------------------------------------------
template <typename T>
unsigned int Array<T>::size() const {
	return size_;
}

// --------------------------------------------------------------------
template <typename T>
void Array<T>::DeepcopyMembers(const Array &other) {
	size_  = other.size();
	array_ = new T[size_];
	for (unsigned int i = 0; i < size_; i++) {
		array_[i] = other[i];
	}
}

template <typename T>
void Array<T>::ThrowIfIndexOutOfRange(const unsigned int index) const {
	if (index >= size_) {
		throw std::out_of_range("index out of bounds");
	}
}

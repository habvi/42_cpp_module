#include <stdexcept>

template <typename T>
Array<T>::Array() : array_(new T[0]()), size_(0) {}

template <typename T>
Array<T>::Array(const unsigned int n) : array_(new T[n]()), size_(n) {}

template <typename T>
Array<T>::Array(const Array &other) {
	array_ = DupArray(other);
	size_  = other.size_;
}

template <typename T>
Array<T>::~Array() {
	delete[] array_;
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &other) {
	if (this != &other) {
		T *tmp = DupArray(other);
		delete[] array_;
		array_ = tmp;
		size_  = other.size_;
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
T *Array<T>::DupArray(const Array &other) {
	T *tmp = new T[other.size_]();
	for (unsigned int i = 0; i < other.size_; i++) {
		tmp[i] = other.array_[i];
	}
	return tmp;
}

template <typename T>
void Array<T>::ThrowIfIndexOutOfRange(const unsigned int index) const {
	if (index >= size_) {
		throw std::out_of_range("index out of bounds");
	}
}

#include "Serializer.hpp"
#include <stdexcept>

Serializer::Serializer() {}

Serializer::Serializer(const Serializer &s) {
	(void)s;
}

const Serializer &Serializer::operator=(const Serializer &s) {
	(void)s;
	return *this;
}

Serializer::~Serializer() {}

uintptr_t Serializer::serialize(Data *ptr) {
	if (ptr == NULL) {
		throw std::invalid_argument("argument is NULL");
	}
	return reinterpret_cast<uintptr_t>(ptr);
}

Data *Serializer::deserialize(uintptr_t raw) {
	return reinterpret_cast<Data *>(raw);
}

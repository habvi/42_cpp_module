#ifndef EX01_SERIALIZER_HPP
#define EX01_SERIALIZER_HPP

#include <cstdint>
struct Data;

class Serializer {
  public:
	static uintptr_t serialize(Data *ptr);
	static Data     *deserialize(uintptr_t raw);

  private:
	Serializer();
	Serializer(const Serializer &s);
	const Serializer &operator=(const Serializer &s);
	~Serializer();
};

#endif /* EX01_SERIALIZER_HPP */

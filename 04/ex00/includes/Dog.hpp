#ifndef EX00_DOG_HPP
#define EX00_DOG_HPP

#include "Animal.hpp"
#include <string>

class Dog : public Animal {
  public:
	Dog();
	Dog(const std::string &name);
	Dog(const Dog &d);
	const Dog &operator=(const Dog &d);
	~Dog();

  public:
	// Following the instructions, not camelcase.
	void makeSound() const;
};

#endif /* EX00_DOG_HPP */

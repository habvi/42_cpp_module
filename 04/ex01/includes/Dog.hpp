#ifndef EX01_DOG_HPP
#define EX01_DOG_HPP

#include "Animal.hpp"
#include <string>

class Dog : virtual public Animal {
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

#endif /* EX01_DOG_HPP */

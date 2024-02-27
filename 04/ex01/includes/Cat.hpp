#ifndef EX01_CAT_HPP
#define EX01_CAT_HPP

#include "Animal.hpp"
#include <string>

class Cat : virtual public Animal {
  public:
	Cat();
	Cat(const std::string &name);
	Cat(const Cat &c);
	const Cat &operator=(const Cat &c);
	~Cat();

  public:
	// Following the instructions, not camelcase.
	void makeSound() const;
};

#endif /* EX01_CAT_HPP */

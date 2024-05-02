#ifndef EX00_CAT_HPP
#define EX00_CAT_HPP

#include "Animal.hpp"
#include <string>

class Cat : public Animal {
  public:
	Cat();
	Cat(const std::string &name);
	Cat(const Cat &c);
	Cat &operator=(const Cat &c);
	~Cat();

  public:
	// Following the instructions, not camelcase.
	void makeSound() const;
};

#endif /* EX00_CAT_HPP */

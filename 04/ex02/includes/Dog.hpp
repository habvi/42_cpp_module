#ifndef EX02_DOG_HPP
#define EX02_DOG_HPP

#include "Animal.hpp"
#include <string>

class Brain;

class Dog : public Animal {
  public:
	Dog();
	Dog(const std::string &name);
	Dog(const Dog &d);
	Dog &operator=(const Dog &d);
	~Dog();

  public:
	// Following the instructions, not camelcase.
	void makeSound() const;

  public:
	Brain &GetBrain() const;

  private:
	void CopyBrain(const Dog &d);

  private:
	Brain *brain_;
};

#endif /* EX02_DOG_HPP */

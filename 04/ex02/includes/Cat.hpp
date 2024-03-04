#ifndef EX02_CAT_HPP
#define EX02_CAT_HPP

#include "Animal.hpp"
#include <string>

class Brain;

class Cat : public Animal {
  public:
	Cat();
	Cat(const std::string &name);
	Cat(const Cat &c);
	const Cat &operator=(const Cat &c);
	~Cat();

  public:
	// Following the instructions, not camelcase.
	void makeSound() const;

  public:
	Brain &GetBrain() const;

  private:
	void CopyBrain(const Cat &c);

  private:
	Brain *brain_;
};

#endif /* EX02_CAT_HPP */

#ifndef EX01_WRONG_CAT_HPP
#define EX01_WRONG_CAT_HPP

#include "WrongAnimal.hpp"
#include <string>

class WrongCat : virtual public WrongAnimal {
  public:
	WrongCat();
	WrongCat(const std::string &name);
	WrongCat(const WrongCat &w);
	const WrongCat &operator=(const WrongCat &w);
	~WrongCat();

  public:
	// Following the instructions, not camelcase.
	void makeSound() const;
};

#endif /* EX01_WRONG_CAT_HPP */
#ifndef EX02_WRONG_ANIMAL_HPP
#define EX02_WRONG_ANIMAL_HPP

#include <string>

class WrongAnimal {
  public:
	WrongAnimal();
	WrongAnimal(const WrongAnimal &w);
	WrongAnimal &operator=(const WrongAnimal &w);
	virtual ~WrongAnimal();

  public:
	// Following the instructions, not camelcase.
	std::string getType() const;
	void        makeSound() const;

  protected:
	void SetType(const std::string &name);

  protected:
	std::string type;
};

#endif /* EX02_WRONG_ANIMAL_HPP */

#ifndef EX01_WRONG_ANIMAL_HPP
#define EX01_WRONG_ANIMAL_HPP

#include <string>

class WrongAnimal {
  public:
	WrongAnimal();
	WrongAnimal(const WrongAnimal &w);
	const WrongAnimal &operator=(const WrongAnimal &w);
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

#endif /* EX01_WRONG_ANIMAL_HPP */

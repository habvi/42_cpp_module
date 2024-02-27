#ifndef EX01_ANIMAL_HPP
#define EX01_ANIMAL_HPP

#include <string>

class Animal {
  public:
	Animal();
	Animal(const Animal &a);
	const Animal &operator=(const Animal &a);
	virtual ~Animal();

  public:
	// Following the instructions, not camelcase.
	std::string  getType() const;
	virtual void makeSound() const;

  protected:
	void SetType(const std::string &name);

  protected:
	std::string type;
};

#endif /* EX01_ANIMAL_HPP */

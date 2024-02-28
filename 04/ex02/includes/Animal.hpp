#ifndef EX01_ANIMAL_HPP
#define EX01_ANIMAL_HPP

#include <string>

class Animal {
  public:
	virtual ~Animal();

  public:
	// Following the instructions, not camelcase.
	std::string  getType() const;
	virtual void makeSound() const = 0;

  protected:
	Animal();
	Animal(const Animal &a);
	const Animal &operator=(const Animal &a);
	void          SetType(const std::string &name);

  protected:
	std::string type;
};

#endif /* EX01_ANIMAL_HPP */

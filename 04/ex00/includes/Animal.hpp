#ifndef EX00_ANIMAL_HPP
#define EX00_ANIMAL_HPP

#include <string>

class Animal {
  public:
	Animal();
	Animal(const Animal &a);
	Animal &operator=(const Animal &a);
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

#endif /* EX00_ANIMAL_HPP */

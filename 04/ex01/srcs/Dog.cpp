#include "Dog.hpp"
#include "Brain.hpp"
#include "color.hpp"
#include <iostream>
#include <string>

#define TYPE_DOG  "Dog"
#define SOUND_DOG "woof woof"

Dog::Dog() : Animal() {
	std::cerr << "Default constructor called (" TYPE_DOG ")" << std::endl;
	SetType(TYPE_DOG);
	// todo: for new fail, throw exception
	brain_ = new Brain;
}

Dog::Dog(const std::string &name) : Animal() {
	std::cerr << "Constructor called (" TYPE_DOG ")" << std::endl;
	SetType(name);
	// todo: for new fail, throw exception
	brain_ = new Brain;
}

void Dog::CopyBrain(const Dog &d) {
	// todo: for new fail, throw exception
	brain_ = new Brain(d.GetBrain());
}

Dog::Dog(const Dog &d) : Animal(d) {
	std::cerr << "Coppy constructor called (" TYPE_DOG ")" << std::endl;
	SetType(d.getType());
	CopyBrain(d);
}

const Dog &Dog::operator=(const Dog &d) {
	std::cerr << "Copy assignment operator= called (" TYPE_DOG ")" << std::endl;
	if (this != &d) {
		SetType(d.getType());

		delete brain_;
		CopyBrain(d);
	}
	return *this;
}

Dog::~Dog() {
	std::cerr << "Destructor called (" TYPE_DOG ")" << std::endl;
	delete brain_;
}

// override
void Dog::makeSound() const {
	std::cout << COLOR_GREEN "(" TYPE_DOG ") \\ " SOUND_DOG " /" COLOR_END
			  << std::endl;
}

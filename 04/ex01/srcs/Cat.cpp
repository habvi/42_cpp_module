#include "Cat.hpp"
#include "Brain.hpp"
#include "color.hpp"
#include <iostream>
#include <string>

#define TYPE_CAT  "Cat"
#define SOUND_CAT "meow meow"

Cat::Cat() : Animal() {
	std::cerr << "Default constructor called (" TYPE_CAT ")" << std::endl;
	SetType(TYPE_CAT);
	// todo: for new fail, throw exception
	brain_ = new Brain;
}

Cat::Cat(const std::string &name) : Animal() {
	std::cerr << "Constructor called (" TYPE_CAT ")" << std::endl;
	SetType(name);
	// todo: for new fail, throw exception
	brain_ = new Brain;
}

void Cat::CopyBrain(const Cat &c) {
	// todo: for new fail, throw exception
	brain_ = new Brain(c.GetBrain());
}

Cat::Cat(const Cat &c) : Animal(c) {
	std::cerr << "Coppy constructor called (" TYPE_CAT ")" << std::endl;
	SetType(c.getType());
	CopyBrain(c);
}

const Cat &Cat::operator=(const Cat &c) {
	std::cerr << "Copy assignment operator= called (" TYPE_CAT ")" << std::endl;
	if (this != &c) {
		SetType(c.getType());

		delete brain_;
		CopyBrain(c);
	}
	return *this;
}

Cat::~Cat() {
	std::cerr << "Destructor called (" TYPE_CAT ")" << std::endl;
	delete brain_;
}

// override
void Cat::makeSound() const {
	std::cout << COLOR_PINK "(" TYPE_CAT ") \\ " SOUND_CAT " /" COLOR_END
			  << std::endl;
}

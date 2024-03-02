#include "Cat.hpp"
#include "color.hpp"
#include <iostream>

#define TYPE_CAT  "Cat"
#define SOUND_CAT "meow meow"

Cat::Cat() : Animal() {
	std::cerr << "Default constructor called (" TYPE_CAT ")" << std::endl;
	SetType(TYPE_CAT);
}

Cat::Cat(const std::string &name) : Animal() {
	std::cerr << "Constructor called (" TYPE_CAT ")" << std::endl;
	SetType(name);
}

Cat::Cat(const Cat &c) : Animal(c) {
	std::cerr << "Coppy constructor called (" TYPE_CAT ")" << std::endl;
	SetType(c.getType());
}

const Cat &Cat::operator=(const Cat &c) {
	std::cerr << "Copy assignment operator= called (" TYPE_CAT ")" << std::endl;
	if (this != &c) {
		SetType(c.getType());
	}
	return *this;
}

Cat::~Cat() {
	std::cerr << "Destructor called (" TYPE_CAT ")" << std::endl;
}

// override
void Cat::makeSound() const {
	std::cout << COLOR_PINK "(" TYPE_CAT ") \\ " SOUND_CAT " /" COLOR_END
			  << std::endl;
}

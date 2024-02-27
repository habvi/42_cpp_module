#include "Dog.hpp"
#include "color.hpp"
#include <iostream>
#include <string>

#define TYPE_DOG "Dog"

Dog::Dog() : Animal() {
	std::cerr << "Default constructor called (" TYPE_DOG ")" << std::endl;
	SetType(TYPE_DOG);
}

Dog::Dog(const std::string &name) : Animal() {
	std::cerr << "Constructor called (" TYPE_DOG ")" << std::endl;
	SetType(name);
}

Dog::Dog(const Dog &d) : Animal(d) {
	std::cerr << "Coppy constructor called (" TYPE_DOG ")" << std::endl;
	SetType(d.getType());
}

const Dog &Dog::operator=(const Dog &d) {
	std::cerr << "Copy assignment operator= called (" TYPE_DOG ")" << std::endl;
	if (this != &d) {
		SetType(d.getType());
	}
	return *this;
}

Dog::~Dog() {
	std::cerr << "Destructor called (" TYPE_DOG ")" << std::endl;
}

// override
void Dog::makeSound() const {
	std::cout << COLOR_GREEN "(" TYPE_DOG ") \\ woof woof /" COLOR_END << std::endl;
}

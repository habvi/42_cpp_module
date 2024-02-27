#include "Animal.hpp"
#include "color.hpp"
#include <iostream>
#include <string>

#define TYPE_ANIMAL "Animal"

Animal::Animal() : type(TYPE_ANIMAL) {
	std::cerr << "Default constructor called (" TYPE_ANIMAL ")" << std::endl;
}

Animal::Animal(const Animal &a) : type(a.getType()) {
	std::cerr << "Copy constructor called (" TYPE_ANIMAL ")" << std::endl;
}

const Animal &Animal::operator=(const Animal &a) {
	std::cerr << "Copy assignment operator= called (" TYPE_ANIMAL ")" << std::endl;
	if (this != &a) {
		SetType(a.getType());
	}
	return *this;
}

Animal::~Animal() {
	std::cerr << "Destructor called (" TYPE_ANIMAL ")" << std::endl;
}

std::string Animal::getType() const {
	return type;
}

void Animal::SetType(const std::string &name) {
	type = name;
}

void Animal::makeSound() const {
	std::cout << COLOR_BLUE "(" TYPE_ANIMAL ") ..." COLOR_END << std::endl;
}

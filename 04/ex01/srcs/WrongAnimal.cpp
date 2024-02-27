#include "WrongAnimal.hpp"
#include "color.hpp"
#include <iostream>
#include <string>

#define TYPE_WRONG_ANIMAL  "WrongAnimal"
#define SOUND_WRONG_ANIMAL "..."

WrongAnimal::WrongAnimal() : type(TYPE_WRONG_ANIMAL) {
	std::cerr << "Default constructor called (" TYPE_WRONG_ANIMAL ")" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &a) : type(a.getType()) {
	std::cerr << "Copy constructor called (" TYPE_WRONG_ANIMAL ")" << std::endl;
}

const WrongAnimal &WrongAnimal::operator=(const WrongAnimal &a) {
	std::cerr << "Copy assignment operator= called (" TYPE_WRONG_ANIMAL ")"
			  << std::endl;
	if (this != &a) {
		SetType(a.getType());
	}
	return *this;
}

WrongAnimal::~WrongAnimal() {
	std::cerr << "Destructor called (" TYPE_WRONG_ANIMAL ")" << std::endl;
}

std::string WrongAnimal::getType() const {
	return type;
}

void WrongAnimal::SetType(const std::string &name) {
	type = name;
}

void WrongAnimal::makeSound() const {
	std::cout << COLOR_BLUE "(" TYPE_WRONG_ANIMAL ") \\ " SOUND_WRONG_ANIMAL
							" /" COLOR_END
			  << std::endl;
}

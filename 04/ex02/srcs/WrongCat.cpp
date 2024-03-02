#include "WrongCat.hpp"
#include "color.hpp"
#include <iostream>

#define TYPE_WRONG_CAT  "WrongCat"
#define SOUND_WRONG_CAT "wmeow wmeow"

WrongCat::WrongCat() : WrongAnimal() {
	std::cerr << "Default constructor called (" TYPE_WRONG_CAT ")" << std::endl;
	SetType(TYPE_WRONG_CAT);
}

WrongCat::WrongCat(const std::string &name) : WrongAnimal() {
	std::cerr << "Constructor called (" TYPE_WRONG_CAT ")" << std::endl;
	SetType(name);
}

WrongCat::WrongCat(const WrongCat &c) : WrongAnimal(c) {
	std::cerr << "Coppy constructor called (" TYPE_WRONG_CAT ")" << std::endl;
	SetType(c.getType());
}

const WrongCat &WrongCat::operator=(const WrongCat &c) {
	std::cerr << "Copy assignment operator= called (" TYPE_WRONG_CAT ")"
			  << std::endl;
	if (this != &c) {
		SetType(c.getType());
	}
	return *this;
}

WrongCat::~WrongCat() {
	std::cerr << "Destructor called (" TYPE_WRONG_CAT ")" << std::endl;
}

// overload
void WrongCat::makeSound() const {
	std::cout << COLOR_PINK "(" TYPE_WRONG_CAT ") \\ " SOUND_WRONG_CAT " /" COLOR_END
			  << std::endl;
}

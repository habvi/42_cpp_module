#include "Ice.hpp"
#include "AMateria.hpp"
#include "color.hpp"
#include <iostream>
#include <new>

#define TYPE_ICE "ice"

Ice::Ice() : AMateria(TYPE_ICE) {}

Ice::Ice(const std::string &type) : AMateria(type) {}

Ice::Ice(const Ice &i) : AMateria(i.getType()) {}

const Ice &Ice::operator=(const Ice &i) {
	if (this != &i) {
		AMateria::operator=(i);
	}
	return *this;
}

Ice::~Ice() {}

// if new failed, return NULL;
Ice *Ice::clone() const {
	return new (std::nothrow) Ice();
}

// override
void Ice::use(ICharacter &target) {
	std::cout << COLOR_BLUE "* shoots an ice bolt at " << target.getName()
			  << " *" COLOR_END << std::endl;
}

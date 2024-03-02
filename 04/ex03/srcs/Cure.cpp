#include "Cure.hpp"
#include "AMateria.hpp"
#include "color.hpp"
#include <iostream>
#include <new>

#define TYPE_CURE "cure"

Cure::Cure() : AMateria(TYPE_CURE) {}

Cure::Cure(const std::string &type) : AMateria(type) {}

Cure::Cure(const Cure &c) : AMateria(c.getType()) {}

const Cure &Cure::operator=(const Cure &c) {
	if (this != &c) {
		AMateria::operator=(c);
	}
	return *this;
}

Cure::~Cure() {}

// if new failed, return NULL;
Cure *Cure::clone() const {
	return new (std::nothrow) Cure();
}

// override
void Cure::use(ICharacter &target) {
	std::cout << COLOR_PINK "* heals " << target.getName() << "'s wounds *" COLOR_END
			  << std::endl;
}

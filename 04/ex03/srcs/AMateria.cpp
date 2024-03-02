#include "AMateria.hpp"
#include <iostream>

AMateria::AMateria() {}

AMateria::AMateria(const std::string &type) : type_(type) {}

AMateria::AMateria(const AMateria &a) : type_(a.getType()) {}

const AMateria &AMateria::operator=(const AMateria &a) {
	if (this != &a) {
		type_ = a.getType();
	}
	return *this;
}

AMateria::~AMateria() {}

void AMateria::use(ICharacter &target) {
	std::cerr << "Character's name: " << target.getName() << std::endl;
}

const std::string &AMateria::getType() const {
	return type_;
}

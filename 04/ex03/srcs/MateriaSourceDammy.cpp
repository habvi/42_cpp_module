#include "MateriaSourceDammy.hpp"
#include <iostream>

MateriaSourceDammy::MateriaSourceDammy() {}

MateriaSourceDammy::MateriaSourceDammy(const MateriaSourceDammy &m) {
	(void)m;
}

const MateriaSourceDammy &MateriaSourceDammy::operator=(const MateriaSourceDammy &m
) {
	(void)m;
	return *this;
}

MateriaSourceDammy::~MateriaSourceDammy() {}

void MateriaSourceDammy::learnMateria(AMateria *a) {
	(void)a;
	std::cout << "MateriaSourceDammy class: learnMateria()" << std::endl;
}

AMateria *MateriaSourceDammy::createMateria(const std::string &materia_type) {
	(void)materia_type;
	std::cout << "MateriaSourceDammy class: createMateria()" << std::endl;
	return NULL;
}

#include "MateriaSource.hpp"
#include "AMateria.hpp"

MateriaSource::MateriaSource() : num_of_srcs_(0) {
	for (unsigned int i = 0; i < kLimitCharactersNum; i++) {
		materia_srcs_[i] = NULL;
	}
}

void MateriaSource::copyMateriaSrcs(const MateriaSource &m) {
	// assert
	for (unsigned int i = 0; i < kLimitCharactersNum; i++) {
		if (m.materia_srcs_[i]) {
			materia_srcs_[i] = m.materia_srcs_[i]->clone();
			// todo: throw exception
		} else {
			materia_srcs_[i] = NULL;
		}
	}
}

MateriaSource::MateriaSource(const MateriaSource &m)
	: num_of_srcs_(m.getNumOfSrcs()) {
	// todo: try-catch
	copyMateriaSrcs(m);
}

const MateriaSource &MateriaSource::operator=(const MateriaSource &m) {
	if (this != &m) {
		num_of_srcs_ = m.getNumOfSrcs();
		for (unsigned int i = 0; i < kLimitCharactersNum; i++) {
			delete materia_srcs_[i];
		}
		// todo: try-catch
		copyMateriaSrcs(m);
	}
	return *this;
}

MateriaSource::~MateriaSource() {
	for (unsigned int i = 0; i < num_of_srcs_; i++) {
		delete materia_srcs_[i];
	}
}

void MateriaSource::learnMateria(AMateria *a) {
	if (a == NULL || num_of_srcs_ >= kLimitCharactersNum) {
		return;
	}
	materia_srcs_[num_of_srcs_] = a;
	num_of_srcs_++;
}

// When the materia_type does not exist or clone()'s new fails, NULL is returned"
AMateria *MateriaSource::createMateria(const std::string &materia_type) {
	for (unsigned int i = 0; i < num_of_srcs_; i++) {
		if (materia_srcs_[i]->getType() == materia_type) {
			return materia_srcs_[i]->clone();
		}
	}
	return NULL;
}

unsigned int MateriaSource::getNumOfSrcs() const {
	return num_of_srcs_;
}

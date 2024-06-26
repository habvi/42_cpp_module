#ifndef EX03_MateriaSourceDammy_HPP
#define EX03_MateriaSourceDammy_HPP

#include "IMateriaSource.hpp"
#include <string>

class AMateria;

class MateriaSourceDammy : public IMateriaSource {
  public:
	MateriaSourceDammy();
	MateriaSourceDammy(const MateriaSourceDammy &m);
	MateriaSourceDammy &operator=(const MateriaSourceDammy &m);
	~MateriaSourceDammy();

  public:
	void      learnMateria(AMateria *a);
	AMateria *createMateria(const std::string &materia_type);
};

#endif /* EX03_MateriaSourceDammy_HPP */

#ifndef EX03_MateriaSource_HPP
#define EX03_MateriaSource_HPP

#include "IMateriaSource.hpp"
#include <string>

class AMateria;

class MateriaSource : public IMateriaSource {
  public:
	MateriaSource();
	MateriaSource(const MateriaSource &m);
	MateriaSource &operator=(const MateriaSource &m);
	~MateriaSource();

  public:
	void      learnMateria(AMateria *a);
	AMateria *createMateria(const std::string &materia_type);

  public:
	unsigned int getNumOfSrcs() const;
	AMateria    *getIthAMateria(const unsigned int index) const;

  private:
	void copyMateriaSrcs(const MateriaSource &m);

  private:
	static const unsigned int kLimitCharactersNum = 4;
	unsigned int              num_of_srcs_;
	AMateria                 *materia_srcs_[kLimitCharactersNum];
};

#endif /* EX03_MateriaSource_HPP */

#ifndef EX03_IMateriaSource_HPP
#define EX03_IMateriaSource_HPP

#include <string>

class AMateria;

// This class definition is in accordance with the subject.
class IMateriaSource {
  public:
	virtual ~IMateriaSource() {}
	virtual void      learnMateria(AMateria *)               = 0;
	virtual AMateria *createMateria(std::string const &type) = 0;
};

#endif /* EX03_IMateriaSource_HPP */

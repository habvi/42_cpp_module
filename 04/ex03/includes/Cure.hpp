#ifndef EX03_CURE_HPP
#define EX03_CURE_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <string>

class Cure : public AMateria {
  public:
	Cure();
	explicit Cure(std::string const &type);
	Cure(const Cure &c);
	Cure &operator=(const Cure &c);
	~Cure();

  public:
	Cure *clone() const;
	void  use(ICharacter &target);
};

#endif /* EX03_CURE_HPP */

#ifndef EX03_ICE_HPP
#define EX03_ICE_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <string>

class Ice : public AMateria {
  public:
	Ice();
	explicit Ice(std::string const &type);
	Ice(const Ice &i);
	Ice &operator=(const Ice &i);
	~Ice();

  public:
	Ice *clone() const;
	void use(ICharacter &target);
};

#endif /* EX03_ICE_HPP */

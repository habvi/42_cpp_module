#ifndef EX03_AMateria_HPP
#define EX03_AMateria_HPP

#include "ICharacter.hpp"
#include <string>

class AMateria {
  public:
	virtual ~AMateria();

  public:
	virtual AMateria *clone() const = 0;
	virtual void      use(ICharacter &target);

  public:
	std::string const &getType() const;

  protected:
	AMateria();
	explicit AMateria(std::string const &type);
	AMateria(const AMateria &a);
	AMateria &operator=(const AMateria &a);

  private:
	std::string type_;
};

#endif /* EX03_AMateria_HPP */

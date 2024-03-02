#ifndef EX03_CHARACTER_HPP
#define EX03_CHARACTER_HPP

#include "ICharacter.hpp"
#include <string>

class AMateria;

class Character : virtual public ICharacter {
  public:
	Character();
	explicit Character(const std::string &name);
	Character(const Character &c);
	const Character &operator=(const Character &c);
	~Character();

  public:
	void equip(AMateria *a);
	void unequip(int idx);
	void use(int idx, ICharacter &target);

  public:
	std::string const &getName() const;
	unsigned int       getLimitSlotNum() const;
	AMateria          *getIthAMateria(const unsigned int index) const;

  private:
	void initMaterias();
	void copyMaterias(const Character &c);
	bool isValidIndex(const int index) const;

  private:
	std::string               name_;
	static const unsigned int kLimitSlotNum = 4;
	AMateria                 *slot_[kLimitSlotNum];
};

#endif /* EX03_CHARACTER_HPP */

#ifndef HUMAN_B_H
#define HUMAN_B_H

#include "Weapon.hpp"
#include <string>

#define COLOR_RED "\033[31m"
#define COLOR_END "\033[0m"

class HumanB {
  public:
	HumanB(const std::string &name);
	HumanB(const std::string &name, Weapon *weapon);
	~HumanB();

  public:
	void setWeapon(Weapon &weapon);
	void attack() const;

  private:
	std::string name_;
	Weapon     *weapon_;
};

#endif /* HUMAN_B_H */

#ifndef HUMAN_A_H
#define HUMAN_A_H

#include "Weapon.hpp"
#include <string>

class HumanA {
  public:
	HumanA(const std::string &name, Weapon &weapon);
	~HumanA();

  public:
	void attack() const;

  private:
	std::string name_;
	Weapon     &weapon_;
};

#endif /* HUMAN_A_H */

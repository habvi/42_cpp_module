#ifndef FLAG_TRAP_H
#define FLAG_TRAP_H

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
  public:
	explicit FragTrap(const std::string &name);
	~FragTrap();

  public:
	// Following the instructions, not camelcase and const qualifier isn't used.
	void highFivesGuys(void);

  private:
	static const unsigned int kInitialHitPoints    = 100;
	static const unsigned int kInitialEnergyPoints = 100;
	static const unsigned int kInitialAttackDamage = 30;
};

#endif /* FLAG_TRAP_H */

#ifndef FLAG_TRAP_H
#define FLAG_TRAP_H

#include "ClapTrap.hpp"
#include <string>

class FragTrap : public ClapTrap {
  public:
	explicit FragTrap(const std::string &name);
	FragTrap(const FragTrap &f);
	~FragTrap();
	FragTrap &operator=(const FragTrap &f);

  public:
	// Following the instructions, not camelcase and const qualifier isn't used.
	void highFivesGuys(void);

  private:
	FragTrap();

  private:
	static const unsigned int kInitialHitPoints    = 100;
	static const unsigned int kInitialEnergyPoints = 100;
	static const unsigned int kInitialAttackDamage = 30;
};

#endif /* FLAG_TRAP_H */

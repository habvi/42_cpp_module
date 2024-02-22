#ifndef FLAG_TRAP_H
#define FLAG_TRAP_H

#include "ClapTrap.hpp"

class FragTrap : public virtual ClapTrap {
  public:
	explicit FragTrap(const std::string &name);
	FragTrap(const FragTrap &f);
	~FragTrap();
	const FragTrap &operator=(const FragTrap &f);

  public:
	// Following the instructions, not camelcase and const qualifier isn't used.
	void highFivesGuys(void);

  protected:
	FragTrap();
	static const unsigned int kInitialHitPoints    = 100;
	static const unsigned int kInitialAttackDamage = 30;

  private:
	static const unsigned int kInitialEnergyPoints = 100;
};

#endif /* FLAG_TRAP_H */

#ifndef SCAV_TRAP_H
#define SCAV_TRAP_H

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
  public:
	explicit ScavTrap(const std::string &name);
	~ScavTrap();

  public:
	// Following the instructions, not camelcase.
	void guardGate() const;

  private:
	ScavTrap();

  private:
	static const unsigned int kInitialHitPoints    = 100;
	static const unsigned int kInitialEnergyPoints = 50;
	static const unsigned int kInitialAttackDamage = 20;
};

#endif /* SCAV_TRAP_H */

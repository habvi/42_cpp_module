#ifndef SCAV_TRAP_H
#define SCAV_TRAP_H

#include "ClapTrap.hpp"
#include <string>

class ScavTrap : public virtual ClapTrap {
  public:
	explicit ScavTrap(const std::string &name);
	ScavTrap(const ScavTrap &s);
	~ScavTrap();
	ScavTrap &operator=(const ScavTrap &s);

  public:
	// Following the instructions, not camelcase.
	void attack(const std::string &target);
	void guardGate() const;

  protected:
	ScavTrap();
	static const unsigned int kInitialEnergyPoints = 50;

  private:
	static const unsigned int kInitialHitPoints    = 100;
	static const unsigned int kInitialAttackDamage = 20;
};

#endif /* SCAV_TRAP_H */

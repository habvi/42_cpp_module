#ifndef DIAMOND_TRAP_H
#define DIAMOND_TRAP_H

#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <string>

class DiamondTrap : public ScavTrap, public FragTrap {
  public:
	explicit DiamondTrap(const std::string &name);
	DiamondTrap(const DiamondTrap &d);
	~DiamondTrap();
	DiamondTrap &operator=(const DiamondTrap &d);

  public:
	// Following the instructions, not camelcase and const qualifier isn't used.
	void whoAmI(void);
	void attack(const std::string &target);

  public:
	const std::string &GetName() const;

  private:
	DiamondTrap();

  private:
	// same variable’s name than the one in the ClapTrap base class.
	std::string name_;
};

#endif /* DIAMOND_TRAP_H */

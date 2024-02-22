#ifndef DIAMOND_TRAP_H
#define DIAMOND_TRAP_H

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

static const std::string nama_surfix = "_clap_name";

class DiamondTrap : public ScavTrap, public FragTrap {
  public:
	explicit DiamondTrap(const std::string &name);
	DiamondTrap(const DiamondTrap &d);
	~DiamondTrap();
	const DiamondTrap &operator=(const DiamondTrap &d);

  public:
	// Following the instructions, not camelcase and const qualifier isn't used.
	void whoAmI(void);

  public:
	const std::string &GetName() const;

  private:
	DiamondTrap();

  private:
	// same variable’s name than the one in the ClapTrap base class.
	std::string name_;
};

#endif /* DIAMOND_TRAP_H */

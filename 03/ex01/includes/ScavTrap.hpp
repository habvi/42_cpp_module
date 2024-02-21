#ifndef SCAV_TRAP_H
#define SCAV_TRAP_H

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
  public:
	explicit ScavTrap(const std::string &name);
	~ScavTrap();
};

#endif /* SCAV_TRAP_H */

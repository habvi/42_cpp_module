#include "ScavTrap.hpp"
#include <iostream>
#include <string>

#define COLOR_GREEN   "\033[32m"
#define COLOR_PINK    "\033[35m"
#define COLOR_END     "\033[0m"

#define NAME_SCAVTRAP "ScavTrap"

ScavTrap::ScavTrap() : ClapTrap() {
	std::cout << "Default constructor called (" NAME_SCAVTRAP ")" << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
	std::cout << "Constructor called (" NAME_SCAVTRAP ")" << std::endl;
	SetHitPoints(kInitialHitPoints);
	SetEnergyPoints(kInitialEnergyPoints);
	SetAttackDamage(kInitialAttackDamage);
}

// copy constructor
ScavTrap::ScavTrap(const ScavTrap &s) : ClapTrap(s) {
	std::cout << "Copy constructor called (" NAME_SCAVTRAP ")" << std::endl;
	SetHitPoints(kInitialHitPoints);
	SetEnergyPoints(kInitialEnergyPoints);
	SetAttackDamage(kInitialAttackDamage);
}

ScavTrap::~ScavTrap() {
	std::cout << "Destructor called (" NAME_SCAVTRAP ")" << std::endl;
}

// copy assignment operator overload
ScavTrap &ScavTrap::operator=(const ScavTrap &s) {
	if (this != &s) {
		ClapTrap::operator=(s);
	}
	return *this;
}

// override ClapTrap's attack()
void ScavTrap::attack(const std::string &target) {
	if (!IsActionPossible()) {
		return;
	}
	std::cout << COLOR_GREEN NAME_SCAVTRAP " " << GetName() << " attacks " << target
			  << ", causing " << GetAttackDamage() << " points of damage!" COLOR_END
			  << std::endl;
}

void ScavTrap::guardGate() const {
	std::cout << COLOR_PINK NAME_SCAVTRAP " " << GetName()
			  << " is now in Gate keeper mode" COLOR_END << std::endl;
}

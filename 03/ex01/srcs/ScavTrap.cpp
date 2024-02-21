#include "ScavTrap.hpp"
#include <iostream>
#include <string>

ScavTrap::ScavTrap(const std::string &name)
	: ClapTrap(name, kInitialHitPoints, kInitialEnergyPoints, kInitialAttackDamage) {
	std::cout << "Constructor called (ScavTrap)" << std::endl;
}

ScavTrap::~ScavTrap() {
	std::cout << "Destructor called (ScavTrap)" << std::endl;
}
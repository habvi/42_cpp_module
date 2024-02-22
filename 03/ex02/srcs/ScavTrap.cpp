#include "ScavTrap.hpp"
#include <iostream>
#include <string>

#define COLOR_PINK "\033[35m"
#define COLOR_END  "\033[0m"

ScavTrap::ScavTrap() : ClapTrap() {}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
	std::cout << "Constructor called (ScavTrap)" << std::endl;
	SetHitPoints(kInitialHitPoints);
	SetEnergyPoints(kInitialEnergyPoints);
	SetAttackDamage(kInitialAttackDamage);
}

ScavTrap::~ScavTrap() {
	std::cout << "Destructor called (ScavTrap)" << std::endl;
}

void ScavTrap::guardGate() const {
	std::cout << COLOR_PINK "ScavTrap " << GetName()
			  << " is now in Gate keeper mode" COLOR_END << std::endl;
}
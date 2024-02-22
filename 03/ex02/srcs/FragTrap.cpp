#include "FragTrap.hpp"
#include <iostream>
#include <string>

#define COLOR_PINK "\033[35m"
#define COLOR_END  "\033[0m"

FragTrap::FragTrap() : ClapTrap() {}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name) {
	std::cout << "Constructor called (FragTrap)" << std::endl;
	SetHitPoints(kInitialHitPoints);
	SetEnergyPoints(kInitialEnergyPoints);
	SetAttackDamage(kInitialAttackDamage);
}

// copy constructor
FragTrap::FragTrap(const FragTrap &f) : ClapTrap(f) {
	std::cout << "Copy constructor called (FragTrap)" << std::endl;
	SetHitPoints(kInitialHitPoints);
	SetEnergyPoints(kInitialEnergyPoints);
	SetAttackDamage(kInitialAttackDamage);
}

FragTrap::~FragTrap() {
	std::cout << "Destructor called (FragTrap)" << std::endl;
}

void FragTrap::highFivesGuys() {
	std::cout << COLOR_PINK "FragTrap " << GetName()
			  << " requests positive high fives." COLOR_END << std::endl;
}

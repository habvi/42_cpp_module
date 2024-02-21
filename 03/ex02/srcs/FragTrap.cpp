#include "FragTrap.hpp"
#include <iostream>
#include <string>

#define COLOR_PINK "\033[35m"
#define COLOR_END  "\033[0m"

FragTrap::FragTrap(const std::string &name)
	: ClapTrap(name, kInitialHitPoints, kInitialEnergyPoints, kInitialAttackDamage) {
	std::cout << "Constructor called (FragTrap)" << std::endl;
}

FragTrap::~FragTrap() {
	std::cout << "Destructor called (FragTrap)" << std::endl;
}

void FragTrap::highFivesGuys() {
	std::cout << COLOR_PINK "FragTrap " << GetName()
			  << " requests positive high fives." COLOR_END << std::endl;
}

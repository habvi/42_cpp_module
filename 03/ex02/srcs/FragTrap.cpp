#include "FragTrap.hpp"
#include <iostream>
#include <string>

#define COLOR_PINK    "\033[35m"
#define COLOR_END     "\033[0m"

#define NAME_FRAGTRAP "FragTrap"

FragTrap::FragTrap() : ClapTrap() {
	std::cout << "Default constructor called (" NAME_FRAGTRAP ")" << std::endl;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name) {
	std::cout << "Constructor called (" NAME_FRAGTRAP ")" << std::endl;
	SetHitPoints(kInitialHitPoints);
	SetEnergyPoints(kInitialEnergyPoints);
	SetAttackDamage(kInitialAttackDamage);
}

// copy constructor
FragTrap::FragTrap(const FragTrap &f) : ClapTrap(f) {
	std::cout << "Copy constructor called (" NAME_FRAGTRAP ")" << std::endl;
	SetHitPoints(kInitialHitPoints);
	SetEnergyPoints(kInitialEnergyPoints);
	SetAttackDamage(kInitialAttackDamage);
}

FragTrap::~FragTrap() {
	std::cout << "Destructor called (" NAME_FRAGTRAP ")" << std::endl;
}

// copy assignment operator overload
FragTrap &FragTrap::operator=(const FragTrap &f) {
	if (this != &f) {
		ClapTrap::operator=(f);
	}
	return *this;
}

void FragTrap::highFivesGuys() {
	std::cout << COLOR_PINK NAME_FRAGTRAP " " << GetName()
			  << " requests positive high fives." COLOR_END << std::endl;
}

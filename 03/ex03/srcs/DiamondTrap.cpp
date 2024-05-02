#include "DiamondTrap.hpp"
#include <iostream>
#include <string>

#define COLOR_PINK       "\033[35m"
#define COLOR_END        "\033[0m"

#define CLAPNAME_SURFIX  "_clap_name"
#define NAME_DIAMONDTRAP "DaimondTrap"

DiamondTrap::DiamondTrap() : ClapTrap(), ScavTrap(), FragTrap() {
	std::cout << "Default constructor called (" NAME_DIAMONDTRAP ")" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string &name)
	: ClapTrap(name + CLAPNAME_SURFIX), ScavTrap(), FragTrap(), name_(name) {
	std::cout << "Constructor called (" NAME_DIAMONDTRAP ")" << std::endl;
	SetHitPoints(FragTrap::kInitialHitPoints);
	SetEnergyPoints(ScavTrap::kInitialEnergyPoints);
	SetAttackDamage(FragTrap::kInitialAttackDamage);
}

// copy constructor
DiamondTrap::DiamondTrap(const DiamondTrap &d)
	: ClapTrap(d), ScavTrap(d), FragTrap(d), name_(d.GetName()) {
	std::cout << "Copy constructor called (" NAME_DIAMONDTRAP ")" << std::endl;
	SetHitPoints(d.GetHitPoints());
	SetEnergyPoints(d.GetEnergyPoints());
	SetAttackDamage(d.GetAttackDamage());
}

DiamondTrap::~DiamondTrap() {
	std::cout << "Destructor called (" NAME_DIAMONDTRAP ")" << std::endl;
}

// copy assignment operator overload
DiamondTrap &DiamondTrap::operator=(const DiamondTrap &d) {
	if (this != &d) {
		ClapTrap::operator=(d);
		SetHitPoints(d.GetHitPoints());
		SetEnergyPoints(d.GetEnergyPoints());
		SetAttackDamage(d.GetAttackDamage());
	}
	return *this;
}

void DiamondTrap::whoAmI() {
	std::cout << COLOR_PINK "My (" NAME_DIAMONDTRAP ") name is " << name_ << "."
			  << std::endl;
	std::cout << "My parent name is " << ClapTrap::GetName() << COLOR_END
			  << std::endl;
}

const std::string &DiamondTrap::GetName() const {
	return name_;
}

// override the parent class's attack().
void DiamondTrap::attack(const std::string &target) {
	ScavTrap::attack(target);
}

#include "DiamondTrap.hpp"
#include <iostream>
#include <string>

#define COLOR_PINK "\033[35m"
#define COLOR_END  "\033[0m"

DiamondTrap::DiamondTrap() : ClapTrap() {}

DiamondTrap::DiamondTrap(const std::string &name)
	: ClapTrap(name + nama_surfix), name_(name) {
	std::cout << "Constructor called (DiamondTrap)" << std::endl;
	SetHitPoints(FragTrap::kInitialHitPoints);
	SetEnergyPoints(ScavTrap::kInitialEnergyPoints);
	SetAttackDamage(FragTrap::kInitialAttackDamage);
}

// copy constructor
DiamondTrap::DiamondTrap(const DiamondTrap &d)
	: ClapTrap(d), ScavTrap(d), FragTrap(d), name_(d.GetName()) {
	std::cout << "Copy constructor called (DiamondTrap)" << std::endl;
	SetHitPoints(d.GetHitPoints());
	SetEnergyPoints(d.GetEnergyPoints());
	SetAttackDamage(d.GetAttackDamage());
}

DiamondTrap::~DiamondTrap() {
	std::cout << "Destructor called (DiamondTrap)" << std::endl;
}

// copy assignment operator overload
const DiamondTrap &DiamondTrap::operator=(const DiamondTrap &d) {
	if (this != &d) {
		ClapTrap::operator=(d);
		SetHitPoints(d.GetHitPoints());
		SetEnergyPoints(d.GetEnergyPoints());
		SetAttackDamage(d.GetAttackDamage());
	}
	return *this;
}

void DiamondTrap::whoAmI() {
	std::cout << COLOR_PINK "My (DiamondTrap) name is " << name_ << "." << std::endl;
	std::cout << "My parent (ClapTrap) name is " << ClapTrap::GetName() << COLOR_END
			  << std::endl;
}

const std::string &DiamondTrap::GetName() const {
	return name_;
}

void DiamondTrap::attack(const std::string &target) {
	ScavTrap::attack(target);
}

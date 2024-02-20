#include "ClapTrap.hpp"
#include <iostream>

#define COLOR_GREEN "\033[32m"
#define COLOR_END   "\033[0m"

ClapTrap::ClapTrap() {
	std::cout << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
	: name_(name), hit_points_(10), energy_points_(10), attack_damage_(0) {
	std::cout << "Constructor called" << std::endl;
}

// copy constructor
ClapTrap::ClapTrap(const ClapTrap &c)
	: name_(c.GetName()),
	  hit_points_(c.GetHitPoints()),
	  energy_points_(c.GetEnergyPoints()),
	  attack_damage_(c.GetAttackDamage()) {
	std::cout << "Copy constructor called" << std::endl;
}

ClapTrap::~ClapTrap() {
	std::cout << "Destructor called" << std::endl;
}

// copy assignment operator overload
const ClapTrap &ClapTrap::operator=(const ClapTrap &c) {
	if (this != &c) {
		name_          = c.GetName();
		hit_points_    = c.GetHitPoints();
		energy_points_ = c.GetEnergyPoints();
		attack_damage_ = c.GetAttackDamage();
	}
	return *this;
}

void ClapTrap::attack(const std::string &target) {
	std::cout << COLOR_GREEN "ClapTrap " << name_ << " attacks " << target
			  << ", causing " << attack_damage_ << " points of damage!" COLOR_END
			  << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	(void)amount;
}

void ClapTrap::btRepaired(unsigned int amount) {
	(void)amount;
}

const std::string &ClapTrap::GetName() const {
	return name_;
}

unsigned int ClapTrap::GetHitPoints() const {
	return hit_points_;
}

unsigned int ClapTrap::GetEnergyPoints() const {
	return energy_points_;
}

unsigned int ClapTrap::GetAttackDamage() const {
	return attack_damage_;
}

void ClapTrap::SetAttackDamage(unsigned int damages) {
	attack_damage_ = damages;
}

void ClapTrap::PutStatus() const {
	std::cout << "----------------------" << std::endl;
	std::cout << "Name          : " << name_ << std::endl;
	std::cout << "Hit points    : " << hit_points_ << std::endl;
	std::cout << "Energy points : " << energy_points_ << std::endl;
	std::cout << "Attack damege : " << attack_damage_ << std::endl;
	std::cout << "----------------------" << std::endl;
}

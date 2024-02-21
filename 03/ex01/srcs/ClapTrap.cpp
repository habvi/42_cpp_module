#include "ClapTrap.hpp"
#include <climits>
#include <iostream>

#define COLOR_RED   "\033[31m"
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

// action : attack or defence
bool ClapTrap::IsActionPossible() const {
	return (hit_points_ > 0) && (energy_points_ > 0);
}

void ClapTrap::attack(const std::string &target) {
	if (!IsActionPossible()) {
		return;
	}
	std::cout << COLOR_GREEN "ClapTrap " << name_ << " attacks " << target
			  << ", causing " << attack_damage_ << " points of damage!" COLOR_END
			  << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (!IsActionPossible()) {
		return;
	}
	if (hit_points_ < amount) {
		std::cout << COLOR_GREEN "ClapTrap " << name_ << " takes damages "
				  << hit_points_
				  << ", since hit points were not remaining that much." COLOR_END
				  << std::endl;
		hit_points_ = 0;
	} else {
		hit_points_ -= amount;
		std::cout << COLOR_GREEN "ClapTrap " << name_ << " takes " << amount
				  << " damages. Hit points are left with " << hit_points_
				  << "." COLOR_END << std::endl;
	}
}

void ClapTrap::LoseEnergyPoint() {
	if (!IsActionPossible()) {
		return;
	}
	energy_points_--;
	std::cout << COLOR_GREEN "ClapTrap " << name_
			  << " successfully attacked, losing 1 energy point, leaving "
			  << energy_points_ << " remaining " COLOR_END << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (!IsActionPossible()) {
		return;
	}
	unsigned int repaired_amount;
	if (hit_points_ >= UINT_MAX - amount) {
		repaired_amount = UINT_MAX - hit_points_;
	} else {
		repaired_amount = amount;
	}
	hit_points_ += repaired_amount;
	energy_points_--;
	std::cout << COLOR_GREEN "ClapTrap " << name_
			  << " successfully repaired itself + " << repaired_amount
			  << " Hit points. New Hit points is " << hit_points_
			  << ", losing 1 energy point, leaving " << energy_points_
			  << " remaining " COLOR_END << std::endl;
}

void ClapTrap::AttackToDefender(
	ClapTrap &defender, const std::string &target, const unsigned int damages
) {
	if (!IsActionPossible() || !defender.IsActionPossible()) {
		std::cerr << COLOR_RED "ClapTrap " << name_ << " failed to attack to "
				  << target << COLOR_END << std::endl;
		return;
	}
	SetAttackDamage(damages);
	attack(target);
	defender.takeDamage(damages);
	LoseEnergyPoint();
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

void ClapTrap::SetAttackDamage(const unsigned int damages) {
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

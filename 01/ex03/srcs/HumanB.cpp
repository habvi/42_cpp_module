#include "HumanB.hpp"
#include <iostream>
#include <string>

HumanB::HumanB(const std::string &name) : name_(name), weapon_(NULL) {}

HumanB::HumanB(const std::string &name, Weapon *weapon)
	: name_(name), weapon_(weapon) {}

HumanB::~HumanB() {}

// NULL is not passed to reference
void HumanB::setWeapon(Weapon &weapon) {
	weapon_ = &weapon;
}

void HumanB::attack() const {
	if (weapon_ == NULL) {
		std::cerr << name_ << " has" COLOR_RED " no weapon" COLOR_END << std::endl;
		return;
	}
	std::cout << name_ << " attacks with their " << weapon_->getType() << std::endl;
}

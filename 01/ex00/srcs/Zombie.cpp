#include "Zombie.hpp"
#include <iostream>
#include <string>

Zombie::Zombie() {
	name_ = "";
}

Zombie::Zombie(const std::string &name) {
	name_ = name;
}

Zombie::~Zombie() {
	std::cerr << COLOR_PINK << name_ << ZOMBIE_DEAD << COLOR_END << std::endl;
}

void Zombie::announce(void) const {
	std::cout << name_ << ": " << ZOMBIE_SOUND << std::endl;
}

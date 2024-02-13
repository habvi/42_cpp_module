#include "Zombie.hpp"
#include <iostream>
#include <string>

Zombie::Zombie() {}

Zombie::Zombie(const std::string &name) {
	name_ = name;
}

Zombie::Zombie(const Zombie &z) {
	name_ = z.name_;
}

Zombie::~Zombie() {
	std::cerr << COLOR_PINK << name_ << ZOMBIE_DEAD << COLOR_END << std::endl;
}

void Zombie::announce(void) const {
	std::cout << name_ << ": " << ZOMBIE_SOUND << std::endl;
}

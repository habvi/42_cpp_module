#include "Zombie.hpp"
#include <string>

// todo: throw error?
Zombie *newZombie(std::string name) {
	Zombie *zombie = new Zombie(name);

	return zombie;
}

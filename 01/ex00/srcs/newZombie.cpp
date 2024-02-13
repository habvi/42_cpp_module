#include "Zombie.hpp"
#include <new>
#include <string>

Zombie *newZombie(std::string name) {
	Zombie *zombie = new (std::nothrow) Zombie(name);

	return zombie;
}

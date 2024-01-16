#include "Zombie.hpp"
#include <iostream>
#include <string>

static void put_error(const std::string &message) {
	std::cerr << COLOR_RED << message << COLOR_END << std::endl << std::endl;
}

Zombie *zombieHorde(int numOfZombies, std::string name) {
	if (numOfZombies < 0) {
		put_error(ERR_NUM_OF_ZOMBIES);
		return NULL;
	}

	Zombie *zombies = new Zombie[numOfZombies];

	// call copy_constructor -> call destructor
	for (int i = 0; i < numOfZombies; i++) {
		zombies[i] = Zombie(name);
	}
	return zombies;
}

#include "Zombie.hpp"
#include <iostream>
#include <new>
#include <string>

static void PutError(const std::string &message) {
	std::cerr << COLOR_RED << "Error: " << message << COLOR_END << std::endl
			  << std::endl;
}

Zombie *zombieHorde(int numOfZombies, std::string name) {
	if (numOfZombies < 0) {
		PutError(ERR_NUM_OF_ZOMBIES);
		return NULL;
	}

	Zombie *zombies = new (std::nothrow) Zombie[numOfZombies];
	if (zombies == NULL) {
		PutError(ERR_ALLOCATE);
		return (NULL);
	}

	// call copy_constructor -> call destructor
	for (int i = 0; i < numOfZombies; i++) {
		zombies[i] = Zombie(name);
	}
	return zombies;
}

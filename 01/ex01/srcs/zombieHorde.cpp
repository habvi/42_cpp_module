#include "Zombie.hpp"
#include <iostream>
#include <new>
#include <string>

static void PutError(const std::string &message) {
	std::cerr << COLOR_RED << "Error: " << message << COLOR_END << std::endl
			  << std::endl;
}

Zombie *zombieHorde(int num_of_zombies, std::string name) {
	if (num_of_zombies < 0) {
		PutError(ERR_NUM_OF_ZOMBIES);
		return NULL;
	}

	Zombie *zombies = new (std::nothrow) Zombie[num_of_zombies];
	if (zombies == NULL) {
		PutError(ERR_ALLOCATE);
		return (NULL);
	}

	// call copy_constructor -> call destructor
	for (int i = 0; i < num_of_zombies; i++) {
		zombies[i] = Zombie(name);
	}
	return zombies;
}

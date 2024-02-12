#include "Zombie.hpp"
#include <cstdlib>
#include <iostream>

static void displayTitle(const std::string &title, const int numOfZombies) {
	std::cout << "┃ test: " << title << numOfZombies << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void announceEachZombies(const Zombie *zombies, const int n) {
	for (int i = 0; i < n; i++) {
		zombies[i].announce();
	}
}

static void run_test(const int numOfZombies) {
	displayTitle("number of zombies = ", numOfZombies);

	Zombie *zombies = zombieHorde(numOfZombies, "abcd");
	if (zombies == NULL) {
		return;
	}
	announceEachZombies(zombies, numOfZombies);
	// call destructor
	delete[] zombies;

	std::cout << std::endl;
}

int main() {
	/* normal case */
	run_test(4);
	run_test(0);
	run_test(2);

	/* error case (N = minus) */
	run_test(-5);
	run_test(-100);

	return EXIT_SUCCESS;
}

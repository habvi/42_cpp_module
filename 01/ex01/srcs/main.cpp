#include "Zombie.hpp"
#include <cstdlib>
#include <iostream>

static void DisplayTitle(const std::string &title, const int numOfZombies) {
	std::cout << "┃ test: " << title << numOfZombies << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void AnnounceEachZombies(const Zombie *zombies, const int n) {
	for (int i = 0; i < n; i++) {
		zombies[i].announce();
	}
}

static void RunTest(const int numOfZombies) {
	DisplayTitle("number of zombies = ", numOfZombies);

	Zombie *zombies = zombieHorde(numOfZombies, "abcd");
	if (zombies == NULL) {
		return;
	}
	AnnounceEachZombies(zombies, numOfZombies);
	// call destructor
	delete[] zombies;

	std::cout << std::endl;
}

int main() {
	/* normal case */
	RunTest(4);
	RunTest(0);
	RunTest(2);

	/* error case (N = minus) */
	RunTest(-5);
	RunTest(-100);

	return EXIT_SUCCESS;
}

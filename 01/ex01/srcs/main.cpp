#include "Zombie.hpp"
#include <cstdlib>
#include <iostream>

static void DisplayTitle(const std::string &title, const int num_of_zombies) {
	std::cout << "┃ test: " << title << num_of_zombies << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void AnnounceEachZombies(const Zombie *zombies, const int n) {
	for (int i = 0; i < n; i++) {
		zombies[i].announce();
	}
}

static void RunTest(const int num_of_zombies) {
	DisplayTitle("number of zombies = ", num_of_zombies);

	Zombie *zombies = zombieHorde(num_of_zombies, "abcd");
	if (zombies == NULL) {
		return;
	}
	AnnounceEachZombies(zombies, num_of_zombies);
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

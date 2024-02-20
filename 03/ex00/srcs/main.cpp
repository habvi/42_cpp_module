#include "ClapTrap.hpp"
#include <cstdlib>
#include <string>

static void PutStatusAandB(const ClapTrap &a, const ClapTrap &b) {
	a.PutStatus();
	b.PutStatus();
}

static void RunOriginalTest() {
	ClapTrap          alice("Alice");
	const std::string target = "Bob";
	ClapTrap          bob(target);

	PutStatusAandB(alice, bob);
}

int main() {
	RunOriginalTest();
	return EXIT_SUCCESS;
}

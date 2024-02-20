#include "ClapTrap.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

#define COLOR_RED "\033[31m"
#define COLOR_END "\033[0m"

static void PutStatusAandB(const ClapTrap &attacker, const ClapTrap &defender) {
	attacker.PutStatus();
	defender.PutStatus();
}

static bool IsEnergyPointsLeft(const ClapTrap &c) {
	return c.GetEnergyPoints() > 0;
}

static bool
AreBothHitPointsLeft(const ClapTrap &attacker, const ClapTrap &defender) {
	return (attacker.GetHitPoints() > 0) && (defender.GetHitPoints() > 0);
}

static void AttackAtoB(
	ClapTrap          &attacker,
	ClapTrap          &defender,
	const std::string &target,
	const unsigned int damages
) {
	if (IsEnergyPointsLeft(attacker) && AreBothHitPointsLeft(attacker, defender)) {
		attacker.SetAttackDamage(damages);
		attacker.attack(target);
		// defender.takeDamage(damages);
		// attacker.LostEnergyPoint();
	} else {
		std::cout << COLOR_RED "Attack failed." COLOR_END << std::endl;
	}
}

static void RunOriginalTest() {
	ClapTrap          alice("Alice");
	const std::string target = "Bob";
	ClapTrap          bob(target);

	PutStatusAandB(alice, bob);
	// Alice attacks Bob normal
	AttackAtoB(alice, bob, target, 4);
	PutStatusAandB(alice, bob);
}

int main() {
	RunOriginalTest();
	return EXIT_SUCCESS;
}

#include "ClapTrap.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

#define COLOR_RED "\033[31m"
#define COLOR_END "\033[0m"

static void DisplayTitle(const std::string &title) {
	std::cout << "\n┃ test: " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void Line() {
	std::cout << "----------------------" << std::endl;
}

static void PutStatusAandB(const ClapTrap &attacker, const ClapTrap &defender) {
	attacker.PutStatus();
	defender.PutStatus();
}

static bool IsAttackableAtoB(const ClapTrap &attacker, const ClapTrap &defender) {
	return attacker.IsActionPossible() && defender.IsActionPossible();
}

static void AttackAtoB(
	ClapTrap          &attacker,
	ClapTrap          &defender,
	const std::string &target,
	const unsigned int damages
) {
	if (IsAttackableAtoB(attacker, defender)) {
		attacker.SetAttackDamage(damages);
		attacker.attack(target);
		defender.takeDamage(damages);
		attacker.LoseEnergyPoint();
	} else {
		std::cout << COLOR_RED "Attack failed." COLOR_END << std::endl;
	}
}

static void RunTest1() {
	DisplayTitle("No Hit Points");

	ClapTrap    alice("Alice");
	std::string target = "Bob";
	ClapTrap    bob(target);

	PutStatusAandB(alice, bob);

	// Alice -> Bob. Success.
	AttackAtoB(alice, bob, target, 4);
	PutStatusAandB(alice, bob);
	// damages >= hit_points
	AttackAtoB(alice, bob, target, 8);
	PutStatusAandB(alice, bob);
	// 0 damages. Nothing happend.
	AttackAtoB(alice, bob, target, 0);
	PutStatusAandB(alice, bob);

	// Bob -> Alice. Bob has no hit_points. Nothing happend.
	target = "Alice";
	AttackAtoB(bob, alice, target, 5);
	PutStatusAandB(alice, bob);
}

static void RunOriginalTest() {
	RunTest1();
}

int main() {
	RunOriginalTest();
	return EXIT_SUCCESS;
}

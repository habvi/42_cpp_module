#include "ClapTrap.hpp"
#include <climits>
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
		std::cerr << COLOR_RED "(main) Attack failed." COLOR_END << std::endl;
	}
}

static bool IsRepaireable(const ClapTrap &c) {
	return c.IsActionPossible();
}

static void Repaire(ClapTrap &c, const unsigned int points) {
	if (IsRepaireable(c)) {
		c.beRepaired(points);
	} else {
		std::cerr << COLOR_RED "(main) Repair failed." COLOR_END << std::endl;
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

static void RunTest2() {
	DisplayTitle("No Energy points for attack");

	ClapTrap    alice("Alice");
	std::string target = "Bob";
	ClapTrap    bob(target);

	bob.beRepaired(10);
	PutStatusAandB(alice, bob);

	// Alice -> Bob. 10 attacks.
	for (unsigned int i = 0; i < 10; i++) {
		AttackAtoB(alice, bob, target, 1);
		Line();
	}
	PutStatusAandB(alice, bob);

	// Alice -> Bob. Alice has no energy points. Nothing happend.
	AttackAtoB(alice, bob, target, 1);
	PutStatusAandB(alice, bob);
}

static void RunTest3() {
	DisplayTitle("No Energy points for Repaire");

	ClapTrap alice("Alice");
	alice.PutStatus();

	// Alice repaires 10 times.
	for (unsigned int i = 0; i < 10; i++) {
		Repaire(alice, 1);
		Line();
	}
	alice.PutStatus();

	// Alice has no energy points. Nothing happend.
	Repaire(alice, 1);
	alice.PutStatus();
}

static void RunTest4() {
	DisplayTitle("Repaire overflow");

	ClapTrap alice("Alice");
	alice.beRepaired(UINT_MAX - 20);
	alice.PutStatus();

	// Max Hit points.
	Repaire(alice, 11);
	alice.PutStatus();

	Repaire(alice, 0);
	alice.PutStatus();
}

// same behavior test1
static void RunTest5() {
	DisplayTitle("Attack A to B in ClapTrap class");

	ClapTrap    alice("Alice");
	std::string target = "Bob";
	ClapTrap    bob(target);

	PutStatusAandB(alice, bob);

	// Alice -> Bob. Success.
	alice.AttackToDefender(bob, target, 4);
	PutStatusAandB(alice, bob);
	// damages >= hit_points
	alice.AttackToDefender(bob, target, 8);
	PutStatusAandB(alice, bob);
	// 0 damages. Nothing happend.
	alice.AttackToDefender(bob, target, 0);
	PutStatusAandB(alice, bob);

	// Bob -> Alice. Bob has no hit_points. Nothing happend.
	target = "Alice";
	bob.AttackToDefender(alice, target, 5);
	PutStatusAandB(alice, bob);
}

static void RunOriginalTest() {
	RunTest1();
	RunTest2();
	RunTest3();
	RunTest4();
	RunTest5();
}

int main() {
	RunOriginalTest();
	return EXIT_SUCCESS;
}

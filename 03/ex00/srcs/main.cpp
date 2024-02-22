#include "ClapTrap.hpp"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>

#define COLOR_RED   "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_END   "\033[0m"

#define ALICE       "Alice"
#define BOB         "Bob"

static void DisplayTitle(const std::string &title) {
	std::cout << "\n\n┃ test: " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void Line() {
	std::cout << "----------------------" << std::endl;
}

template <typename T>
static void JudgeIsEqual(
	const std::string &message,
	T                 &target,
	const unsigned int expected_hit_points,
	const unsigned int expected_energy_points,
	const unsigned int expected_attack_damage
) {
	std::cout << message << ": ";
	if (target.GetHitPoints() == expected_hit_points &&
		target.GetEnergyPoints() == expected_energy_points &&
		target.GetAttackDamage() == expected_attack_damage) {
		std::cout << COLOR_GREEN "OK" << COLOR_END << std::endl;
	} else {
		std::cout << COLOR_RED "NG" << COLOR_END << std::endl;
		exit(EXIT_FAILURE);
	}
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

	ClapTrap    alice(ALICE);
	ClapTrap    bob(BOB);
	std::string target = BOB;

	PutStatusAandB(alice, bob);
	JudgeIsEqual(" - Alice Init", alice, 10, 10, 0);
	JudgeIsEqual(" - Bob Init  ", bob, 10, 10, 0);

	// Alice -> Bob. Success.
	AttackAtoB(alice, bob, target, 4);
	JudgeIsEqual(" - Alice", alice, 10, 9, 4);
	JudgeIsEqual(" - Bob  ", bob, 6, 10, 0);
	// damages >= hit_points
	AttackAtoB(alice, bob, target, 8);
	JudgeIsEqual(" - Alice", alice, 10, 8, 8);
	JudgeIsEqual(" - Bob  ", bob, 0, 10, 0);
	// 0 damages. Nothing happend.
	AttackAtoB(alice, bob, target, 0);
	JudgeIsEqual(" - Alice", alice, 10, 8, 8);
	JudgeIsEqual(" - Bob  ", bob, 0, 10, 0);

	// Bob -> Alice. Bob has no hit_points. Nothing happend.
	target = ALICE;
	AttackAtoB(bob, alice, target, 5);
	JudgeIsEqual(" - Alice", alice, 10, 8, 8);
	JudgeIsEqual(" - Bob  ", bob, 0, 10, 0);
}

static void RunTest2() {
	DisplayTitle("No Energy points for attack");

	ClapTrap          alice(ALICE);
	ClapTrap          bob(BOB);
	const std::string target = BOB;

	bob.beRepaired(10);
	PutStatusAandB(alice, bob);
	JudgeIsEqual(" - Alice Init", alice, 10, 10, 0);
	JudgeIsEqual(" - Bob Init  ", bob, 20, 9, 0);

	// Alice -> Bob. 10 attacks.
	for (unsigned int i = 0; i < 10; i++) {
		AttackAtoB(alice, bob, target, 1);
		JudgeIsEqual(" - Alice", alice, 10, 10 - i - 1, 1);
		JudgeIsEqual(" - Bob  ", bob, 20 - i - 1, 9, 0);
		Line();
	}

	// Alice -> Bob. Alice has no energy points. Nothing happend.
	AttackAtoB(alice, bob, target, 1);
	JudgeIsEqual(" - Alice", alice, 10, 0, 1);
	JudgeIsEqual(" - Bob  ", bob, 10, 9, 0);
}

static void RunTest3() {
	DisplayTitle("No Energy points for Repaire");

	ClapTrap alice(ALICE);
	alice.PutStatus();
	JudgeIsEqual(" - Alice Init", alice, 10, 10, 0);

	// Alice repaires 10 times.
	for (unsigned int i = 0; i < 10; i++) {
		Repaire(alice, 1);
		JudgeIsEqual(" - Alice", alice, 10 + i + 1, 10 - i - 1, 0);
		Line();
	}

	// Alice has no energy points. Nothing happend.
	Repaire(alice, 1);
	JudgeIsEqual(" - Alice", alice, 20, 0, 0);
}

static void RunTest4() {
	DisplayTitle("Repaire overflow");

	ClapTrap alice(ALICE);
	alice.beRepaired(UINT_MAX - 20);
	alice.PutStatus();
	JudgeIsEqual(" - Alice Init", alice, UINT_MAX - 10, 9, 0);

	// Max Hit points.
	Repaire(alice, 11);
	JudgeIsEqual(" - Alice", alice, UINT_MAX, 8, 0);

	Repaire(alice, 0);
	JudgeIsEqual(" - Alice", alice, UINT_MAX, 7, 0);
}

// same behavior test1
static void RunTest5() {
	DisplayTitle("Attack A to B in ClapTrap class");

	ClapTrap    alice(ALICE);
	ClapTrap    bob(BOB);
	std::string target = BOB;

	PutStatusAandB(alice, bob);
	JudgeIsEqual(" - Alice Init", alice, 10, 10, 0);
	JudgeIsEqual(" - Bob Init  ", bob, 10, 10, 0);

	// Alice -> Bob. Success.
	alice.AttackToDefender(bob, target, 4);
	JudgeIsEqual(" - Alice", alice, 10, 9, 4);
	JudgeIsEqual(" - Bob  ", bob, 6, 10, 0);

	// damages >= hit_points
	alice.AttackToDefender(bob, target, 8);
	JudgeIsEqual(" - Alice", alice, 10, 8, 8);
	JudgeIsEqual(" - Bob  ", bob, 0, 10, 0);

	// 0 damages. Nothing happend.
	alice.AttackToDefender(bob, target, 0);
	JudgeIsEqual(" - Alice", alice, 10, 8, 8);
	JudgeIsEqual(" - Bob  ", bob, 0, 10, 0);

	// Bob -> Alice. Bob has no hit_points. Nothing happend.
	target = ALICE;
	bob.AttackToDefender(alice, target, 5);
	JudgeIsEqual(" - Alice", alice, 10, 8, 8);
	JudgeIsEqual(" - Bob  ", bob, 0, 10, 0);
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

#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
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
	static unsigned int number = 0;

	number++;
	std::cout << "\n\n┃ test " << number << ": " << title << std::endl;
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

template <typename T, typename U>
static void PutStatusAandB(const T &attacker, const U &defender) {
	attacker.PutStatus();
	defender.PutStatus();
}

template <typename T, typename U>
static bool IsAttackableAtoB(const T &attacker, const U &defender) {
	return attacker.IsActionPossible() && defender.IsActionPossible();
}

template <typename T, typename U>
static void AttackAtoB(
	T &attacker, U &defender, const std::string &target, const unsigned int damages
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

template <typename T>
static bool IsRepaireable(const T &trap) {
	return trap.IsActionPossible();
}

template <typename T>
static void Repaire(T &trap, const unsigned int points) {
	if (IsRepaireable(trap)) {
		trap.beRepaired(points);
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

	PutStatusAandB(alice, bob);
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

static void RunTest6() {
	DisplayTitle("ScavTrap class");

	// ClapTrap constructor called -> ScavTrap constructor called
	ScavTrap scav(ALICE);
	scav.PutStatus();
	JudgeIsEqual(" - Alice Init", scav, 100, 50, 20);
	// ScavTrap destructor called -> ClapTrap destructor called
}

static void RunTest7() {
	DisplayTitle("ClapTrap & ScavTrap class");

	ClapTrap                 alice(ALICE);
	ScavTrap                 bob(BOB);
	static const std::string target = ALICE;

	alice.beRepaired(20);
	PutStatusAandB(alice, bob);
	JudgeIsEqual(" - Alice Init", alice, 30, 9, 0);
	JudgeIsEqual(" - Bob Init  ", bob, 100, 50, 20);

	// Bob -> Alice. normal attack
	bob.AttackToDefender(alice, target, 20);
	JudgeIsEqual(" - Alice", alice, 10, 9, 0);
	JudgeIsEqual(" - Bob  ", bob, 100, 49, 20);

	// Bob -> Alice. damages >= hit_points
	bob.AttackToDefender(alice, target, 12);
	JudgeIsEqual(" - Alice", alice, 0, 9, 0);
	JudgeIsEqual(" - Bob  ", bob, 100, 48, 12);

	// Bob -> Alice. Alice has no hit_points. Nothing happend.
	bob.AttackToDefender(alice, target, 10);
	JudgeIsEqual(" - Alice", alice, 0, 9, 0);
	JudgeIsEqual(" - Bob  ", bob, 100, 48, 12);
}

static void RunTest8() {
	DisplayTitle("ScavTrap guard Gate mode");

	ScavTrap scav(ALICE);
	scav.attack(BOB);
	scav.guardGate();
	scav.PutStatus();
	JudgeIsEqual(" - Alice Init", scav, 100, 50, 20);
}

static void RunTest9() {
	DisplayTitle("ScavTrap & ScavTrap class");

	ScavTrap          alice(ALICE);
	ScavTrap          bob(BOB);
	const std::string target = BOB;

	PutStatusAandB(alice, bob);
	JudgeIsEqual(" - Alice Init", alice, 100, 50, 20);
	JudgeIsEqual(" - Bob Init  ", bob, 100, 50, 20);

	// Alice -> Bob. normal attack
	alice.AttackToDefender(bob, target, 20);
	JudgeIsEqual(" - Alice", alice, 100, 49, 20);
	JudgeIsEqual(" - Bob  ", bob, 80, 50, 20);

	// Alice -> Bob. damages >= hit_points
	alice.AttackToDefender(bob, target, 88);
	JudgeIsEqual(" - Alice", alice, 100, 48, 88);
	JudgeIsEqual(" - Bob  ", bob, 0, 50, 20);

	// Alice -> Bob. Alice has no hit_points. Nothing happend.
	alice.AttackToDefender(bob, target, 10);
	JudgeIsEqual(" - Alice", alice, 100, 48, 88);
	JudgeIsEqual(" - Bob  ", bob, 0, 50, 20);
}

static void RunTest10() {
	DisplayTitle("FragTrap class");

	// ClapTrap constructor called -> FragTrap constructor called
	FragTrap f(ALICE);
	f.PutStatus();
	JudgeIsEqual(" - Alice Init", f, 100, 100, 30);
	// FragTrap destructor called -> ClapTrap destructor called
}

static void RunTest11() {
	DisplayTitle("ClapTrap & FragTrap class");

	ClapTrap                 alice(ALICE);
	FragTrap                 bob(BOB);
	static const std::string target = ALICE;

	alice.beRepaired(50);
	PutStatusAandB(alice, bob);
	JudgeIsEqual(" - Alice Init", alice, 60, 9, 0);
	JudgeIsEqual(" - Bob Init  ", bob, 100, 100, 30);

	// Bob -> Alice. normal attack
	bob.AttackToDefender(alice, target, 30);
	JudgeIsEqual(" - Alice", alice, 30, 9, 0);
	JudgeIsEqual(" - Bob  ", bob, 100, 99, 30);

	// Bob -> Alice. damages >= hit_points
	bob.AttackToDefender(alice, target, 120);
	JudgeIsEqual(" - Alice", alice, 0, 9, 0);
	JudgeIsEqual(" - Bob  ", bob, 100, 98, 120);

	// Bob -> Alice. Alice has no hit_points. Nothing happend.
	bob.AttackToDefender(alice, target, 10);
	JudgeIsEqual(" - Alice", alice, 0, 9, 0);
	JudgeIsEqual(" - Bob  ", bob, 100, 98, 120);
}

static void RunTest12() {
	DisplayTitle("FragTrap highFivesGuys()");

	FragTrap f(ALICE);
	f.highFivesGuys();
	f.PutStatus();
	JudgeIsEqual(" - Alice Init", f, 100, 100, 30);
}

static void RunTest13() {
	DisplayTitle("FragTrap & FragTrap class");

	FragTrap          alice(ALICE);
	FragTrap          bob(BOB);
	const std::string target = BOB;

	PutStatusAandB(alice, bob);
	JudgeIsEqual(" - Alice Init", alice, 100, 100, 30);
	JudgeIsEqual(" - Bob Init  ", bob, 100, 100, 30);

	// Alice -> Bob. normal attack
	alice.AttackToDefender(bob, target, 30);
	JudgeIsEqual(" - Alice", alice, 100, 99, 30);
	JudgeIsEqual(" - Bob  ", bob, 70, 100, 30);

	// Alice -> Bob. damages >= hit_points
	alice.AttackToDefender(bob, target, 88);
	JudgeIsEqual(" - Alice", alice, 100, 98, 88);
	JudgeIsEqual(" - Bob  ", bob, 0, 100, 30);

	// Alice -> Bob. Alice has no hit_points. Nothing happend.
	alice.AttackToDefender(bob, target, 10);
	JudgeIsEqual(" - Alice", alice, 100, 98, 88);
	JudgeIsEqual(" - Bob  ", bob, 0, 100, 30);
}

static void RunTest14() {
	DisplayTitle("ScavTrap copy constructor");

	ScavTrap s(ALICE);
	s.PutStatus();
	JudgeIsEqual(" - Alice Init", s, 100, 50, 20);

	ScavTrap s2(s);
	s2.PutStatus();
	JudgeIsEqual(" - Alice Init", s2, 100, 50, 20);
}

static void RunTest15() {
	DisplayTitle("FragTrap copy constructor");

	FragTrap f(ALICE);
	f.PutStatus();
	JudgeIsEqual(" - Alice Init", f, 100, 100, 30);

	FragTrap f2(f);
	f2.PutStatus();
	JudgeIsEqual(" - Alice Init", f, 100, 100, 30);
}

static void RunTest16() {
	DisplayTitle("ScavTrap copy assignment operator overload");

	ScavTrap s(ALICE);
	s.PutStatus();
	JudgeIsEqual(" - Alice Init", s, 100, 50, 20);

	ScavTrap s2 = s;
	s2.PutStatus();
	JudgeIsEqual(" - Alice Init", s2, 100, 50, 20);
}
static void RunTest17() {
	DisplayTitle("FragTrap copy assignment operator overload");

	FragTrap f(ALICE);
	f.PutStatus();
	JudgeIsEqual(" - Alice Init", f, 100, 100, 30);

	FragTrap f2 = f;
	f2.PutStatus();
	JudgeIsEqual(" - Alice Init", f2, 100, 100, 30);
}

static void RunOriginalTest() {
	/* ex00 */
	RunTest1();
	RunTest2();
	RunTest3();
	RunTest4();
	RunTest5();

	/* ex01 */
	RunTest6();
	RunTest7();
	RunTest8();
	RunTest9();

	/* ex02 same bihavior Test6-9*/
	RunTest10();
	RunTest11();
	RunTest12();
	RunTest13();
	RunTest14();
	RunTest15();
	RunTest16();
	RunTest17();
}

int main() {
	RunOriginalTest();
	return EXIT_SUCCESS;
}

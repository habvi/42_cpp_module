#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>

#define COLOR_RED "\033[31m"
#define COLOR_END "\033[0m"

#define ALICE     "Alice"
#define BOB       "Bob"

static void DisplayTitle(const std::string &title) {
	static unsigned int number = 0;

	number++;
	std::cout << "\n┃ test " << number << ": " << title << std::endl;
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

	ClapTrap    alice(ALICE);
	ClapTrap    bob(BOB);
	std::string target = BOB;

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
	target = ALICE;
	AttackAtoB(bob, alice, target, 5);
	PutStatusAandB(alice, bob);
}

static void RunTest2() {
	DisplayTitle("No Energy points for attack");

	ClapTrap          alice(ALICE);
	ClapTrap          bob(BOB);
	const std::string target = BOB;

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

	ClapTrap alice(ALICE);
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

	ClapTrap alice(ALICE);
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

	ClapTrap    alice(ALICE);
	ClapTrap    bob(BOB);
	std::string target = BOB;

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
	target = ALICE;
	bob.AttackToDefender(alice, target, 5);
	PutStatusAandB(alice, bob);
}

static void RunTest6() {
	DisplayTitle("ScavTrap class");

	// ClapTrap constructor called -> ScavTrap constructor called
	ScavTrap scav(ALICE);
	scav.PutStatus();
	// ScavTrap destructor called -> ClapTrap destructor called
}

static void RunTest7() {
	DisplayTitle("ClapTrap & ScavTrap class");

	ClapTrap                 alice(ALICE);
	ScavTrap                 bob(BOB);
	static const std::string target = ALICE;

	alice.beRepaired(20);
	PutStatusAandB(alice, bob);

	// Bob -> Alice. normal attack (default attack_damage)
	bob.AttackToDefender(alice, target);
	PutStatusAandB(alice, bob);

	// Bob -> Alice. damages >= hit_points
	bob.AttackToDefender(alice, target, 12);
	PutStatusAandB(alice, bob);

	// Bob -> Alice. Alice has no hit_points. Nothing happend.
	bob.AttackToDefender(alice, target, 10);
	PutStatusAandB(alice, bob);
}

static void RunTest8() {
	DisplayTitle("ScavTrap guard Gate mode");

	ScavTrap scav(ALICE);
	scav.guardGate();
	scav.PutStatus();
}

static void RunTest9() {
	DisplayTitle("ScavTrap & ScavTrap class");

	ScavTrap          alice(ALICE);
	ScavTrap          bob(BOB);
	const std::string target = BOB;

	PutStatusAandB(alice, bob);

	// Alice -> Bob. normal attack (default attack_damage)
	alice.AttackToDefender(bob, target);
	PutStatusAandB(alice, bob);

	// Alice -> Bob. damages >= hit_points
	alice.AttackToDefender(bob, target, 88);
	PutStatusAandB(alice, bob);

	// Alice -> Bob. Alice has no hit_points. Nothing happend.
	alice.AttackToDefender(bob, target, 10);
	PutStatusAandB(alice, bob);
}

static void RunTest10() {
	DisplayTitle("FragTrap class");

	// ClapTrap constructor called -> FragTrap constructor called
	FragTrap scav(ALICE);
	scav.PutStatus();
	// FragTrap destructor called -> ClapTrap destructor called
}

static void RunTest11() {
	DisplayTitle("ClapTrap & FragTrap class");

	ClapTrap                 alice(ALICE);
	FragTrap                 bob(BOB);
	static const std::string target = ALICE;

	alice.beRepaired(50);
	PutStatusAandB(alice, bob);

	// Bob -> Alice. normal attack (default attack_damage)
	bob.AttackToDefender(alice, target);
	PutStatusAandB(alice, bob);

	// Bob -> Alice. damages >= hit_points
	bob.AttackToDefender(alice, target, 120);
	PutStatusAandB(alice, bob);

	// Bob -> Alice. Alice has no hit_points. Nothing happend.
	bob.AttackToDefender(alice, target, 10);
	PutStatusAandB(alice, bob);
}

static void RunTest12() {
	DisplayTitle("FragTrap highFivesGuys()");

	FragTrap scav(ALICE);
	scav.highFivesGuys();
	scav.PutStatus();
}

static void RunTest13() {
	DisplayTitle("FragTrap & FragTrap class");

	FragTrap          alice(ALICE);
	FragTrap          bob(BOB);
	const std::string target = BOB;

	PutStatusAandB(alice, bob);

	// Alice -> Bob. normal attack (default attack_damage)
	alice.AttackToDefender(bob, target);
	PutStatusAandB(alice, bob);

	// Alice -> Bob. damages >= hit_points
	alice.AttackToDefender(bob, target, 88);
	PutStatusAandB(alice, bob);

	// Alice -> Bob. Alice has no hit_points. Nothing happend.
	alice.AttackToDefender(bob, target, 10);
	PutStatusAandB(alice, bob);
}

static void RunTest14() {
	DisplayTitle("ScavTrap copy constructor");

	ScavTrap s(ALICE);
	s.PutStatus();

	ScavTrap s2(s);
	s2.PutStatus();
}

static void RunTest15() {
	DisplayTitle("FragTrap copy constructor");

	FragTrap f(ALICE);
	f.PutStatus();

	FragTrap f2(f);
	f2.PutStatus();
}

static void RunTest16() {
	DisplayTitle("ScavTrap copy assignment operator overload");

	ScavTrap s(ALICE);
	s.PutStatus();

	ScavTrap s2 = s;
	s2.PutStatus();
}

static void RunTest17() {
	DisplayTitle("FragTrap copy assignment operator overload");

	FragTrap f(ALICE);
	FragTrap f2 = f;
	f.PutStatus();
	f2.PutStatus();
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

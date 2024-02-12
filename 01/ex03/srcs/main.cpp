#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"
#include <cstdlib>
#include <iostream>

// expect both
// "crude spiked club" -> "some other type of club"
int main() {
	{
		Weapon club = Weapon("crude spiked club");
		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	{
		Weapon club = Weapon("crude spiked club");
		HumanB jim("Jim");
		jim.setWeapon(club);
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}
	return EXIT_SUCCESS;
}

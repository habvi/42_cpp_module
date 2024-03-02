#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include <cstdlib>
#include <iostream>

static void DisplayTitle(const std::string &title) {
	static unsigned int number = 0;

	std::cout << "\n\n┃ test " << number << ": " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	number++;
}

static void RunSubjectTest() {
	DisplayTitle("subject");

	// IMateriaSource *src = new MateriaSource();
	// src->learnMateria(new Ice());
	// src->learnMateria(new Cure());

	// ICharacter *me = new Character("me");

	// AMateria *tmp;
	// tmp = src->createMateria("ice");
	// me->equip(tmp);
	// tmp = src->createMateria("cure");
	// me->equip(tmp);

	// ICharacter *bob = new Character("bob-0");

	// me->use(0, *bob); // cout ice's message
	// me->use(1, *bob); // cout cure's message

	// delete bob;
	// delete me;
	// delete src;
}

int main() {
	RunSubjectTest();
	return EXIT_SUCCESS;
}

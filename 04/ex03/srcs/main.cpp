#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"
#include "cassert"
#include "color.hpp"
#include <cstdlib>
#include <iostream>

static void DisplayTitle(const std::string &title) {
	static unsigned int number = 0;

	std::cout << "\n\n┃ test " << number << ": " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	number++;
}

static bool IsDeepCopyBrainMemberArray(const Character *a, const Character *b) {
	assert(a->getLimitSlotNum() == b->getLimitSlotNum());
	for (unsigned int i = 0; i < a->getLimitSlotNum(); i++) {
		AMateria *tmp1 = a->getIthAMateria(i);
		AMateria *tmp2 = b->getIthAMateria(i);
		if (tmp1 && tmp2) {
			if (tmp1->getType() != tmp2->getType()) {
				return false;
			}
		};
	}
	return true;
}

static void JudgeIsEqualMaterias(const Character *a, const Character *b) {
	if (IsDeepCopyBrainMemberArray(a, b)) {
		std::cout << COLOR_GREEN "[deepcopy: OK]" << COLOR_END << std::endl;
	} else {
		std::cout << COLOR_RED "[deepcopy: NG]" << COLOR_END << std::endl;
		exit(EXIT_FAILURE);
	}
}

static void CallAllMateriasUse(Character *c) {
	for (unsigned int i = 0; i < c->getLimitSlotNum(); i++) {
		if (AMateria *m = c->getIthAMateria(i)) {
			m->use(*c);
		}
	}
}

/* === Expect ===
 * shoots an ice bolt at bob *
 * heals bob's wounds *
 */
static void RunSubjectTest() {
	DisplayTitle("subject");

	IMateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter *me = new Character("me");

	AMateria *tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter *bob = new Character("bob");

	me->use(0, *bob); // cout ice's message
	me->use(1, *bob); // cout cure's message

	delete bob;
	delete me;
	delete src;
}

/* === Expect ===
* shoots an ice bolt at Alice *
* heals Alice's wounds *
* heals Alice's wounds *
[deepcopy: OK]
[deepcopy: OK]
[deepcopy: OK]
[deepcopy: OK]
[deepcopy: OK]
*/
static void Test1() {
	DisplayTitle("Character's deepcopy");

	Character *alice = new Character("Alice");

	alice->equip(new Ice());  // i: 0
	alice->equip(new Cure()); // i: 1
	alice->equip(new Cure()); // i: 2
	CallAllMateriasUse(alice);

	Character  bob1(*alice);
	Character *bob2 = alice;
	Character  bob3 = *alice;
	Character *bob4 = new Character(*alice);
	Character *bob5 = &bob1;

	JudgeIsEqualMaterias(alice, &bob1);
	JudgeIsEqualMaterias(alice, bob2);
	JudgeIsEqualMaterias(alice, &bob3);
	JudgeIsEqualMaterias(alice, bob4);
	JudgeIsEqualMaterias(alice, bob5);

	delete bob4;
	delete alice;
}

/* === Expect ===
 * heals bob's wounds *
 */
static void Test2() {
	DisplayTitle("subject + unequip()");

	IMateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter *me = new Character("me");

	AMateria *materia0_ice = src->createMateria("ice");
	me->equip(materia0_ice);
	AMateria *materia1_cure = src->createMateria("cure");
	me->equip(materia1_cure);

	// Subject: Save the addresses before calling unequip(), or anything else, ...
	// unequip materia0_ice
	me->unequip(0);
	delete materia0_ice;

	ICharacter *bob = new Character("bob-2");

	me->use(0, *bob); // ice -> empty (don’t do anything)
	me->use(1, *bob); // cure

	delete bob;
	delete me;
	delete src;
}

static void RunOriginalTest() {
	Test1();
	Test2();
}

int main() {
	RunSubjectTest();
	RunOriginalTest();
	return EXIT_SUCCESS;
}

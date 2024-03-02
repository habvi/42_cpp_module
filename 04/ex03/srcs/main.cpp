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

static bool
IsDeepCopyMateriaArrayForCharacter(const Character *a, const Character *b) {
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

static bool IsDeepCopyMateriaArrayForMateriaSource(
	const MateriaSource *a, const MateriaSource *b
) {
	assert(a->getNumOfSrcs() == b->getNumOfSrcs());
	for (unsigned int i = 0; i < a->getNumOfSrcs(); i++) {
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

template <typename T>
static void
JudgeIsEqualMaterias(const T *a, const T *b, bool IsEqual(const T *, const T *)) {
	if (IsEqual(a, b)) {
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

static void CallAllSlotUse(ICharacter *ic, ICharacter *c) {
	const unsigned int kLimitSlotNum =
		dynamic_cast<Character *>(ic)->getLimitSlotNum();
	for (unsigned int i = 0; i < kLimitSlotNum; i++) {
		ic->use(i, *c);
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

	JudgeIsEqualMaterias(alice, &bob1, &IsDeepCopyMateriaArrayForCharacter);
	JudgeIsEqualMaterias(alice, bob2, &IsDeepCopyMateriaArrayForCharacter);
	JudgeIsEqualMaterias(alice, &bob3, &IsDeepCopyMateriaArrayForCharacter);
	JudgeIsEqualMaterias(alice, bob4, &IsDeepCopyMateriaArrayForCharacter);
	JudgeIsEqualMaterias(alice, bob5, &IsDeepCopyMateriaArrayForCharacter);

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

	// me->use(0, *bob); // ice -> empty (don’t do anything)
	// me->use(1, *bob); // cure
	CallAllSlotUse(me, bob);

	delete bob;
	delete me;
	delete src;
}

/* === Expect ===
 * shoots an ice bolt at bob *
 * heals bob's wounds *
 */
static void Test3() {
	DisplayTitle("ICharacter->use(idx, ptr): idx out of range");
	IMateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter *me = new Character("me");

	AMateria *materia0_ice = src->createMateria("ice");
	me->equip(materia0_ice);
	AMateria *materia1_cure = src->createMateria("cure");
	me->equip(materia1_cure);

	ICharacter *bob = new Character("bob-3");

	// me->use(0, *bob); // ice
	// me->use(1, *bob); // cure
	// me->use(2, *bob); // empty (don’t do anything)
	// me->use(3, *bob); // empty (don’t do anything)
	CallAllSlotUse(me, bob);

	const unsigned int kLimitSlotNum =
		dynamic_cast<Character *>(me)->getLimitSlotNum();
	me->use(kLimitSlotNum, *bob); // out of range (don’t do anything)

	delete bob;
	delete me;
	delete src;
}

/* === Expect ===
[deepcopy: OK]
[deepcopy: OK]
[deepcopy: OK]
[deepcopy: OK]
[deepcopy: OK]
*/
static void Test4() {
	DisplayTitle("MateriaSource's deepcopy");

	MateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	MateriaSource  copy_src1(*src);
	MateriaSource *copy_src2 = src;
	MateriaSource  copy_src3 = *src;
	MateriaSource *copy_src4 = new MateriaSource(*src);
	MateriaSource *copy_src5 = &copy_src1;

	JudgeIsEqualMaterias(src, &copy_src1, &IsDeepCopyMateriaArrayForMateriaSource);
	JudgeIsEqualMaterias(src, copy_src2, &IsDeepCopyMateriaArrayForMateriaSource);
	JudgeIsEqualMaterias(src, &copy_src3, &IsDeepCopyMateriaArrayForMateriaSource);
	JudgeIsEqualMaterias(src, copy_src4, &IsDeepCopyMateriaArrayForMateriaSource);
	JudgeIsEqualMaterias(src, copy_src5, &IsDeepCopyMateriaArrayForMateriaSource);

	delete copy_src4;
	delete src;
}

static void RunOriginalTest() {
	Test1();
	Test2();
	Test3();
	Test4();
}

int main() {
	RunSubjectTest();
	RunOriginalTest();
	return EXIT_SUCCESS;
}

#include "Animal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "color.hpp"
#include <cassert>
#include <cstdlib>
#include <iostream>

static void DisplayTitle(const std::string &title) {
	static unsigned int number = 0;

	std::cout << "\n\n┃ test " << number << ": " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	number++;
}

static void SetIdeas(Brain &brain) {
	for (unsigned int i = 0; i < brain.GetNumOfIdeas(); i++) {
		std::string idea;
		idea.push_back('a' + i % 26);
		idea.push_back('a' + (i + 1) % 26);
		brain.SetIthIdea(i, idea);
	}
}

static bool IsDeepCopyBrainMemberArray(const Brain &a, const Brain &b) {
	assert(a.GetNumOfIdeas() == b.GetNumOfIdeas());
	for (unsigned int i = 0; i < a.GetNumOfIdeas(); i++) {
		// std::cerr << a.GetIthIdea(i) << "|" << b.GetIthIdea(i) << std::endl;
		if (a.GetIthIdea(i) != b.GetIthIdea(i)) {
			return false;
		}
	}
	return true;
}

static void JudgeIsEqualBrain(const Brain &a, const Brain &b) {
	if (IsDeepCopyBrainMemberArray(a, b)) {
		std::cout << COLOR_GREEN "[OK]" << COLOR_END << std::endl;
	} else {
		std::cout << COLOR_RED "[NG]" << COLOR_END << std::endl;
		exit(EXIT_FAILURE);
	}
}

/* === Expect ===
Dog
Cat
(Cat) \ meow meow /
(Dog) \ woof woof /
(Animal) ...
*/
static void RunSubjectTest() {
	DisplayTitle("subject");

	const Animal *meta = new Animal();
	const Animal *j    = new Dog();
	const Animal *i    = new Cat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();

	delete meta;
	delete j;
	delete i;
}

/* === Expect ===
Dog
Cat
(Animal) ...
(Animal) ...
(Animal) ...
*/
static void RunTest1() {
	DisplayTitle("subject / not pointer");

	const Animal meta = Animal();
	const Animal j    = Dog();
	const Animal i    = Cat();

	std::cout << j.getType() << " " << std::endl;
	std::cout << i.getType() << " " << std::endl;
	i.makeSound();
	j.makeSound();
	meta.makeSound();
}

/* === Expect ===
WrongCat
(WrongAnimal) ...
(WrongAnimal) ...
*/
static void RunTest2() {
	DisplayTitle("WrongAnimal & WrongCat class / non-virtual makeSound()");

	const WrongAnimal *wrong_animal = new WrongAnimal();
	const WrongAnimal *wrong_cat    = new WrongCat();

	std::cout << wrong_cat->getType() << " " << std::endl;
	wrong_cat->makeSound();
	wrong_animal->makeSound();

	delete wrong_animal;
	delete wrong_cat;
}

/* === Expect ===
type: Animal
(Animal) \ ... /
 */
static void RunTest3() {
	DisplayTitle("Animal class");

	const Animal *animal = new Animal();

	std::cout << "type: " << animal->getType() << std::endl;
	animal->makeSound();

	delete animal;
}

/* === Expect ===
type: Dog
(Animal) \ ... /
type: Dog
(Dog) \ woof woof /
*/
static void RunTest4() {
	DisplayTitle("Dog calls Animal functions");

	const Dog *dog = new Dog();

	std::cout << "type: " << dog->Animal::getType() << std::endl;
	dog->Animal::makeSound();

	std::cout << "type: " << dog->getType() << std::endl;
	dog->makeSound();

	delete dog;
}

/* === Expect ===
type: Cat
(Animal) \ ... /
type: Cat
(Cat) \ meow meow /
*/
static void RunTest5() {
	DisplayTitle("Cat calls Animal functions");

	const Cat *cat = new Cat();

	std::cout << "type: " << cat->Animal::getType() << std::endl;
	cat->Animal::makeSound();

	std::cout << "type: " << cat->getType() << std::endl;
	cat->makeSound();

	delete cat;
}

/* === Expect ===
type: Animal
(Animal) \ ... /
type: Animal
(Animal) \ ... /
type: Animal
(Animal) \ ... /
 */
static void RunTest6() {
	DisplayTitle("Animal Copy consrtuctor");

	const Animal *animal = new Animal();

	const Animal  copy_animal(*animal);
	const Animal  copy_animal2 = *animal;
	const Animal *copy_animal3 = new Animal(*animal);

	std::cout << "type: " << copy_animal.getType() << std::endl;
	copy_animal.makeSound();

	std::cout << "type: " << copy_animal2.getType() << std::endl;
	copy_animal2.makeSound();

	std::cout << "type: " << copy_animal3->getType() << std::endl;
	copy_animal3->makeSound();

	delete copy_animal3;
	delete animal;
}

/* === Expect ===
 */
static void RunTest7() {
	DisplayTitle("Dog & Cat construct/destruct *Brain");

	const Dog *dog = new Dog();
	delete dog;

	const Cat *cat = new Cat();
	delete cat;
}

/* === Expect ===
[OK]
[OK]
*/
static void RunTest8() {
	DisplayTitle("Brain constructor / deepcopy");

	Brain *brain = new Brain();
	SetIdeas(*brain);

	const Brain copy_brain(*brain);
	JudgeIsEqualBrain(*brain, copy_brain);

	const Brain copy_brain2 = *brain;
	JudgeIsEqualBrain(*brain, copy_brain2);

	delete brain;
}

/* === Expect ===
type: CopyDog
(Dog) \ woof woof /
[OK]
type: CopyDog
(Dog) \ woof woof /
[OK]
type: CopyDog
(Dog) \ woof woof /
[OK]
*/
static void RunTest9() {
	DisplayTitle("Dog Copy consrtuctor / deepcopy");

	const Dog *dog = new Dog("CopyDog");
	SetIdeas(dog->GetBrain());

	const Dog  copy_dog(*dog);
	const Dog  copy_dog2 = *dog;
	const Dog *copy_dog3 = new Dog(*dog);

	std::cout << "type: " << copy_dog.getType() << std::endl;
	copy_dog.makeSound();
	JudgeIsEqualBrain(dog->GetBrain(), copy_dog.GetBrain());

	std::cout << "type: " << copy_dog2.getType() << std::endl;
	copy_dog2.makeSound();
	JudgeIsEqualBrain(dog->GetBrain(), copy_dog2.GetBrain());

	std::cout << "type: " << copy_dog3->getType() << std::endl;
	copy_dog3->makeSound();
	JudgeIsEqualBrain(dog->GetBrain(), copy_dog3->GetBrain());

	delete copy_dog3;
	delete dog;
}

/* === Expect ===
type: CopyCat
(Cat) \ meow meow /
[OK]
type: CopyCat
(Cat) \ meow meow /
[OK]
type: CopyCat
(Cat) \ meow meow /
[OK]
*/
static void RunTest10() {
	DisplayTitle("Cat Copy consrtuctor / deepcopy");

	const Cat *cat = new Cat("CopyCat");
	SetIdeas(cat->GetBrain());

	const Cat  copy_cat(*cat);
	const Cat  copy_cat2 = *cat;
	const Cat *copy_cat3 = new Cat(*cat);

	std::cout << "type: " << copy_cat.getType() << std::endl;
	copy_cat.makeSound();
	JudgeIsEqualBrain(cat->GetBrain(), copy_cat.GetBrain());

	std::cout << "type: " << copy_cat2.getType() << std::endl;
	copy_cat2.makeSound();
	JudgeIsEqualBrain(cat->GetBrain(), copy_cat2.GetBrain());

	std::cout << "type: " << copy_cat3->getType() << std::endl;
	copy_cat3->makeSound();
	JudgeIsEqualBrain(cat->GetBrain(), copy_cat3->GetBrain());

	delete copy_cat3;
	delete cat;
}

/* === Expect ===
Error: index out of range
*/
static void RunTest11() {
	DisplayTitle("Dog's Brain GetIthIdea() index out of range");

	const Dog *dog = new Dog();
	try {
		dog->GetBrain().GetIthIdea(10000);
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	delete dog;
}

/* === Expect ===
Error: index out of range
*/
static void RunTest12() {
	DisplayTitle("Cat's Brain GetIthIdea() index out of range");

	const Cat *cat = new Cat();
	try {
		cat->GetBrain().GetIthIdea(10000);
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	delete cat;
}

/* === Expect ===
Error: index out of range
*/
static void RunTest13() {
	DisplayTitle("Dog's Brain SetIthIdea() index out of range");

	const Dog *dog = new Dog();
	try {
		dog->GetBrain().SetIthIdea(10000, "out of range");
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	delete dog;
}

/* === Expect ===
Error: index out of range
*/
static void RunTest14() {
	DisplayTitle("Cat's Brain SetIthIdea() index out of range");

	const Cat *cat = new Cat();
	try {
		cat->GetBrain().SetIthIdea(10000, "out of range");
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	delete cat;
}

/* === Expect ===
(Dog) \ woof woof /
(Dog) \ woof woof /
(Dog) \ woof woof /
(Cat) \ meow meow /
(Cat) \ meow meow /
(Cat) \ meow meow /
(Dog) \ woof woof /
(Dog) \ woof woof /
(Dog) \ woof woof /
(Cat) \ meow meow /
(Cat) \ meow meow /
(Cat) \ meow meow /
set 5 from pointer
set 88 from pointer
[OK]
*/
static void RunTest15() {
	DisplayTitle("subject test: array of Animal (half Dog, half Cat)");

	static const unsigned int array_size = 6;
	Animal                   *animals[array_size];

	// half Dog, half Cat
	for (unsigned int i = 0; i < array_size; i++) {
		if (i < array_size / 2) {
			animals[i] = new Dog();
		} else {
			animals[i] = new Cat();
		}
	}
	// makeSound()
	for (unsigned int i = 0; i < array_size; i++) {
		animals[i]->makeSound();
	}
	// set ideas
	Dog *dog = dynamic_cast<Dog *>(animals[1]);
	dog->GetBrain().SetIthIdea(5, "set 5 from pointer");
	dog->GetBrain().SetIthIdea(88, "set 88 from pointer");

	// copy Animal array
	Animal *copy_animals[array_size];
	for (unsigned int i = 0; i < array_size; i++) {
		copy_animals[i] = animals[i];
	}
	// makeSound()
	for (unsigned int i = 0; i < array_size; i++) {
		copy_animals[i]->makeSound();
	}
	// check copy Brain's Ideas. (deepcopy)
	Dog *copy_dog = dynamic_cast<Dog *>(copy_animals[1]);
	std::cout << copy_dog->GetBrain().GetIthIdea(5) << std::endl;
	std::cout << copy_dog->GetBrain().GetIthIdea(88) << std::endl;
	JudgeIsEqualBrain(dog->GetBrain(), copy_dog->GetBrain());

	// delete Animal array
	for (unsigned int i = 0; i < array_size; i++) {
		delete animals[i];
	}
}

static void RunOriginalTest() {
	/* ex00 */
	RunTest1();
	RunTest2();
	RunTest3();
	RunTest4();
	RunTest5();
	RunTest6();

	/* ex01 */
	RunTest7();
	RunTest8();
	RunTest9();
	RunTest10();
	RunTest11();
	RunTest12();
	RunTest13();
	RunTest14();
	RunTest15();
}

int main() {
	RunSubjectTest();
	RunOriginalTest();
	return EXIT_SUCCESS;
}

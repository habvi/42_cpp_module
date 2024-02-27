#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <cstdlib>
#include <iostream>

static void DisplayTitle(const std::string &title) {
	static unsigned int number = 0;

	std::cout << "\n\n┃ test " << number << ": " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	number++;
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

static void RunOriginalTest() {
	RunTest1();
	RunTest2();
}

int main() {
	RunSubjectTest();
	RunOriginalTest();
	return EXIT_SUCCESS;
}

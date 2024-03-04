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
type: CopyDog
(Dog) \ woof woof /
type: CopyDog
(Dog) \ woof woof /
type: CopyDog
(Dog) \ woof woof /
*/
static void RunTest7() {
	DisplayTitle("Dog Copy consrtuctor");

	const Dog *dog = new Dog("CopyDog");

	const Dog  copy_dog(*dog);
	const Dog  copy_dog2 = *dog;
	const Dog *copy_dog3 = new Dog(*dog);

	std::cout << "type: " << copy_dog.getType() << std::endl;
	copy_dog.makeSound();

	std::cout << "type: " << copy_dog2.getType() << std::endl;
	copy_dog2.makeSound();

	std::cout << "type: " << copy_dog3->getType() << std::endl;
	copy_dog3->makeSound();

	delete copy_dog3;
	delete dog;
}

/* === Expect ===
type: CopyCat
(Cat) \ meow meow /
type: CopyCat
(Cat) \ meow meow /
type: CopyCat
(Cat) \ meow meow /
*/
static void RunTest8() {
	DisplayTitle("Cat Copy consrtuctor");

	const Cat *cat = new Cat("CopyCat");

	const Cat  copy_cat(*cat);
	const Cat  copy_cat2 = *cat;
	const Cat *copy_cat3 = new Cat(*cat);

	std::cout << "type: " << copy_cat.getType() << std::endl;
	copy_cat.makeSound();

	std::cout << "type: " << copy_cat2.getType() << std::endl;
	copy_cat2.makeSound();

	std::cout << "type: " << copy_cat3->getType() << std::endl;
	copy_cat3->makeSound();

	delete copy_cat3;
	delete cat;
}

static void RunOriginalTest() {
	RunTest1();
	RunTest2();
	RunTest3();
	RunTest4();
	RunTest5();
	RunTest6();
	RunTest7();
	RunTest8();
}

int main() {
	RunSubjectTest();
	RunOriginalTest();
	return EXIT_SUCCESS;
}

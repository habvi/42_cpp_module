#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include <cstdlib>
#include <iostream>

static void DisplayTitle(const std::string &title) {
	static unsigned int number = 0;

	number++;
	std::cout << "\n\n┃ test " << number << ": " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

int main() {
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

	return EXIT_SUCCESS;
}

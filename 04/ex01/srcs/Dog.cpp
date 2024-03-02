#include "Dog.hpp"
#include "Brain.hpp"
#include "color.hpp"
#include <cstdlib>
#include <iostream>

#define TYPE_DOG  "Dog"
#define SOUND_DOG "woof woof"

Dog::Dog() : Animal() {
	std::cerr << "Default constructor called (" TYPE_DOG ")" << std::endl;
	try {
		brain_ = new Brain;
	} catch (const std::bad_alloc &e) {
		std::cerr << COLOR_RED "Error: failed to allocate: " << e.what() << COLOR_END
				  << std::endl;
		std::exit(EXIT_FAILURE);
	}
	SetType(TYPE_DOG);
}

Dog::Dog(const std::string &name) : Animal() {
	std::cerr << "Constructor called (" TYPE_DOG ")" << std::endl;
	try {
		brain_ = new Brain;
	} catch (const std::bad_alloc &e) {
		std::cerr << COLOR_RED "Error: failed to allocate: " << e.what() << COLOR_END
				  << std::endl;
		std::exit(EXIT_FAILURE);
	}
	SetType(name);
}

void Dog::CopyBrain(const Dog &d) {
	brain_ = new Brain(d.GetBrain());
}

Dog::Dog(const Dog &d) : Animal(d) {
	std::cerr << "Coppy constructor called (" TYPE_DOG ")" << std::endl;
	try {
		CopyBrain(d);
	} catch (const std::bad_alloc &e) {
		std::cerr << COLOR_RED "Error: failed to allocate: " << e.what() << COLOR_END
				  << std::endl;
		std::exit(EXIT_FAILURE);
	}
	SetType(d.getType());
}

const Dog &Dog::operator=(const Dog &d) {
	std::cerr << "Copy assignment operator= called (" TYPE_DOG ")" << std::endl;
	if (this != &d) {
		delete brain_;
		try {
			CopyBrain(d);
		} catch (const std::bad_alloc &e) {
			std::cerr << COLOR_RED "Error: failed to allocate: " << e.what()
					  << COLOR_END << std::endl;
			std::exit(EXIT_FAILURE);
		}
		SetType(d.getType());
	}
	return *this;
}

Dog::~Dog() {
	std::cerr << "Destructor called (" TYPE_DOG ")" << std::endl;
	delete brain_;
}

// override
void Dog::makeSound() const {
	std::cout << COLOR_GREEN "(" TYPE_DOG ") \\ " SOUND_DOG " /" COLOR_END
			  << std::endl;
}

Brain &Dog::GetBrain() const {
	return *brain_;
}

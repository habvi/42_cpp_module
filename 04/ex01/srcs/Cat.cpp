#include "Cat.hpp"
#include "Brain.hpp"
#include "color.hpp"
#include <cstdlib>
#include <iostream>

#define TYPE_CAT  "Cat"
#define SOUND_CAT "meow meow"

Cat::Cat() : Animal() {
	std::cerr << "Default constructor called (" TYPE_CAT ")" << std::endl;
	try {
		brain_ = new Brain;
	} catch (const std::bad_alloc &e) {
		std::cerr << COLOR_RED "Error: failed to allocate: " << e.what() << COLOR_END
				  << std::endl;
		std::exit(EXIT_FAILURE);
	}
	SetType(TYPE_CAT);
}

Cat::Cat(const std::string &name) : Animal() {
	std::cerr << "Constructor called (" TYPE_CAT ")" << std::endl;
	try {
		brain_ = new Brain;
	} catch (const std::bad_alloc &e) {
		std::cerr << COLOR_RED "Error: failed to allocate: " << e.what() << COLOR_END
				  << std::endl;
		std::exit(EXIT_FAILURE);
	}
	SetType(name);
}

void Cat::CopyBrain(const Cat &c) {
	brain_ = new Brain(c.GetBrain());
}

Cat::Cat(const Cat &c) : Animal(c) {
	std::cerr << "Coppy constructor called (" TYPE_CAT ")" << std::endl;
	try {
		CopyBrain(c);
	} catch (const std::bad_alloc &e) {
		std::cerr << COLOR_RED "Error: failed to allocate: " << e.what() << COLOR_END
				  << std::endl;
		std::exit(EXIT_FAILURE);
	}
	SetType(c.getType());
}

const Cat &Cat::operator=(const Cat &c) {
	std::cerr << "Copy assignment operator= called (" TYPE_CAT ")" << std::endl;
	if (this != &c) {
		delete brain_;
		try {
			CopyBrain(c);
		} catch (const std::bad_alloc &e) {
			std::cerr << COLOR_RED "Error: failed to allocate: " << e.what()
					  << COLOR_END << std::endl;
			std::exit(EXIT_FAILURE);
		}
		SetType(c.getType());
	}
	return *this;
}

Cat::~Cat() {
	std::cerr << "Destructor called (" TYPE_CAT ")" << std::endl;
	delete brain_;
}

// override
void Cat::makeSound() const {
	std::cout << COLOR_PINK "(" TYPE_CAT ") \\ " SOUND_CAT " /" COLOR_END
			  << std::endl;
}

Brain &Cat::GetBrain() const {
	return *brain_;
}

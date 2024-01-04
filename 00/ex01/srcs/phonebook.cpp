#include "phonebook.hpp"
#include <iostream>

Phonebook::Phonebook() {}

Phonebook::~Phonebook() {}

void Phonebook::save_contact(const Contact &contact) {
	static unsigned int index = 0;

	index %= LIMIT_REGISTER_COUNT;
	phonebook_[index] = contact;

	std::cout << "\nADD success!" << std::endl;
	// print_specific_contact_(index);
	index++;
}

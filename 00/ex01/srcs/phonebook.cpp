#include "phonebook.hpp"
#include <iostream>

Phonebook::Phonebook() {}

Phonebook::~Phonebook() {}

void Phonebook::save_contact(const Contact &contact) {
	static unsigned int index = 0;

	index %= LIMIT_REGISTER_COUNT;
	phonebook_[index] = contact;

	std::cout << "\nADD success!" << std::endl;
	print_specific_contact_(index);
	index++;
}

// todo: set limit 10 width
void Phonebook::print_name_data_in_contact_(const unsigned int index) {}

void Phonebook::print_specific_contact_(const unsigned int index) {
	std::cout << "┌──────────┬──────────┬──────────┬──────────┐" << std::endl;
	std::cout << "│       No.│first name│ last name│ nick name│" << std::endl;
	std::cout << "├──────────┼──────────┼──────────┼──────────┤" << std::endl;
	print_name_data_in_contact_(index);
	std::cout << "└──────────┴──────────┴──────────┴──────────┘" << std::endl;
}

#include "phonebook.hpp"
#include "contact.hpp"
#include <iostream>

Phonebook::Phonebook() {}

Phonebook::~Phonebook() {}

void Phonebook::save_contact(const Contact &contact) {
	static unsigned int index = 0;

	index %= LIMIT_REGISTER_COUNT;
	phonebook_[index] = contact;

	std::cout << "\nADD success!" << std::endl;
	display_specific_contact_(index);
	index++;
}

static void display_table_header() {
	std::cout << "┌──────────┬──────────┬──────────┬──────────┐" << std::endl
			  << "│       No.│First Name│ Last Name│  Nickname│" << std::endl;
}

static void display_table_middle() {
	std::cout << "├──────────┼──────────┼──────────┼──────────┤" << std::endl;
}

static void display_table_end() {
	std::cout << "└──────────┴──────────┴──────────┴──────────┘" << std::endl;
}

void Phonebook::display_all() const {
	display_table_header();
	for (size_t index = 0; index < LIMIT_REGISTER_COUNT; index++) {
		display_table_middle();
		display_name_data_in_contact_(index);
	}
	display_table_end();
}

void Phonebook::display_name_data_in_contact_(const unsigned int index) const {
	const Contact &contact = phonebook_[index];

	std::cout << "│         " << index << "│         " << contact.first_name()
			  << "│         " << contact.last_name() << "│         "
			  << contact.nick_name() << "│" << std::endl;
}

void Phonebook::display_specific_contact_(const unsigned int index) const {
	display_table_header();
	display_table_middle();
	display_name_data_in_contact_(index);
	display_table_end();
}

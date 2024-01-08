#include "phonebook.hpp"
#include "contact.hpp"
#include <iomanip>
#include <iostream>
#include <string>

Phonebook::Phonebook() {}

Phonebook::~Phonebook() {}

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

static bool is_not_registered(const Contact &contact) {
	return (contact.get_first_name() == "");
}

static const std::string
truncate_str(const std::string &s, const unsigned int max_length) {
	const size_t length = s.size();

	if (length <= max_length) {
		return s;
	} else {
		std::string substr_s = s.substr(0, max_length - 1);
		substr_s.push_back(TRUNCATED_LAST_CHAR);
		return substr_s;
	}
}

static void display_specific_width(const std::string &s, const int column_width) {
	const std::string truncated_str = truncate_str(s, column_width);

	std::cout << std::setw(column_width) << std::right << truncated_str;
}

static void display_specific_width(const unsigned int num, const int column_width) {
	std::cout << std::setw(column_width) << std::right << num;
}

static void display_table_row(const unsigned int index, const Contact &contact) {
	static const int column_width = COLUMN_WIDTH;

	std::cout << "│";
	display_specific_width(index, column_width);
	std::cout << "│";
	display_specific_width(contact.get_first_name(), column_width);
	std::cout << "│";
	display_specific_width(contact.get_last_name(), column_width);
	std::cout << "│";
	display_specific_width(contact.get_nick_name(), column_width);
	std::cout << "│" << std::endl;
}

static void
display_specific_contact_(const unsigned int index, const Contact &contact) {
	display_table_header();
	display_table_middle();
	display_table_row(index, contact);
	display_table_end();
}

void Phonebook::save_contact(const Contact &contact) {
	static unsigned int index = 0;

	index %= LIMIT_REGISTER_COUNT;
	phonebook_[index] = contact;

	display_specific_contact_(index, phonebook_[index]);
	index++;
}

void Phonebook::display_all() const {
	display_table_header();
	for (size_t index = 0; index < LIMIT_REGISTER_COUNT; index++) {
		if (is_not_registered(phonebook_[index])) {
			break;
		}
		display_table_middle();
		display_table_row(index, phonebook_[index]);
	}
	display_table_end();
}

void Phonebook::display_contact_detail_by_index(const unsigned int index) const {
	const Contact &contact = phonebook_[index];

	if (index >= LIMIT_REGISTER_COUNT) {
		std::cout << MSG_INVALID_INDEX << std::endl;
		return;
	}
	contact.display_all();
}

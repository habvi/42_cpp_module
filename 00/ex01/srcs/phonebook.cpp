#include "phonebook.hpp"
#include "color.hpp"
#include "contact.hpp"
#include <iomanip>
#include <iostream>
#include <string>

Phonebook::Phonebook() {}

Phonebook::~Phonebook() {}

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

	std::cout << SEPARATOR << std::setw(column_width) << std::right << truncated_str;
}

static void display_specific_width(const unsigned int num, const int column_width) {
	std::cout << SEPARATOR << std::setw(column_width) << std::right << num;
}

static void display_table_header() {
	static const int column_width = COLUMN_WIDTH;

	std::cout << "┌──────────┬──────────┬──────────┬──────────┐" << std::endl;
	display_specific_width(COLUMN_NO, column_width);
	display_specific_width(FIRST_NAME, column_width);
	display_specific_width(LAST_NAME, column_width);
	display_specific_width(NICK_NAME, column_width);
	std::cout << SEPARATOR << std::endl;
}

static void display_table_middle() {
	std::cout << "├──────────┼──────────┼──────────┼──────────┤" << std::endl;
}

static void display_table_end() {
	std::cout << "└──────────┴──────────┴──────────┴──────────┘" << std::endl;
}

static void display_table_row(const unsigned int index, const Contact &contact) {
	static const int column_width = COLUMN_WIDTH;

	display_specific_width(index, column_width);
	display_specific_width(contact.get_first_name(), column_width);
	display_specific_width(contact.get_last_name(), column_width);
	display_specific_width(contact.get_nick_name(), column_width);
	std::cout << SEPARATOR << std::endl;
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

	phonebook_[index] = contact;
	display_specific_contact_(index, phonebook_[index]);
	index++;
	index %= LIMIT_REGISTER_COUNT;
}

static bool is_not_registered(const Contact &contact) {
	return (contact.get_first_name().empty());
}

void Phonebook::display_all() const {
	Contact contact;

	display_table_header();
	for (size_t index = 0; index < LIMIT_REGISTER_COUNT; index++) {
		contact = phonebook_[index];
		if (is_not_registered(contact)) {
			break;
		}
		display_table_middle();
		display_table_row(index, contact);
	}
	display_table_end();
}

bool Phonebook::is_valid_index(const unsigned int index) const {
	const Contact &contact = phonebook_[index];

	return !(index >= LIMIT_REGISTER_COUNT || is_not_registered(contact));
}

// allow only registered contact index.
void Phonebook::display_contact_detail_by_index(const unsigned int index) const {
	const Contact &contact = phonebook_[index];

	if (!is_valid_index(index)) {
		std::cerr << RED MSG_INVALID_INDEX END << std::endl;
		return;
	}
	contact.display_all();
}

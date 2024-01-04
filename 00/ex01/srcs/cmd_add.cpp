#include "command.hpp"
#include "contact.hpp"
#include "phonebook.hpp"
#include <iomanip>
#include <iostream>

static void input(const std::string &title, std::string &dst) {
	std::cout << std::setw(INPUT_WIDTH) << std::left << title << ": ";
	std::cin >> dst;
}

// todo: not allow empty input
static const t_contact_dto input_data() {
	t_contact_dto data;

	input(FIRST_NAME, data.first_name);
	input(LAST_NAME, data.last_name);
	input(NICK_NAME, data.nick_name);
	input(PHONE_NUMBER, data.phone_number);
	input(DARKEST_SECRET, data.darkest_secret);
	return data;
}

static void convert_data_to_contact(Contact &contact, const t_contact_dto &data) {
	contact = Contact(data);
}

static void input_contact_date(Contact &contact) {
	const t_contact_dto data = input_data();

	convert_data_to_contact(contact, data);
}

void exec_add(Phonebook &phonebook) {
	Contact contact;

	input_contact_date(contact);
	phonebook.save_contact(contact);
}

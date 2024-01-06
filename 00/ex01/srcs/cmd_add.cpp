#include "command.hpp"
#include "contact.hpp"
#include "phonebook.hpp"
#include "utils.hpp"
#include <iostream>

// todo: not allow empty input
static const t_contact_dto input_data() {
	t_contact_dto      data;
	const unsigned int width = INPUT_WIDTH;

	input_left_align(FIRST_NAME, data.first_name, width);
	input_left_align(LAST_NAME, data.last_name, width);
	input_left_align(NICK_NAME, data.nick_name, width);
	input_left_align(PHONE_NUMBER, data.phone_number, width);
	input_left_align(DARKEST_SECRET, data.darkest_secret, width);
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

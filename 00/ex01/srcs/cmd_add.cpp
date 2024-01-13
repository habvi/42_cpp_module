#include "command.hpp"
#include "contact.hpp"
#include "io.hpp"
#include "phonebook.hpp"
#include <iostream>
#include <string>

// The field isn't allowed to be an empty string.
static t_result input_each_data(const std::string &title, std::string &dst) {
	const t_result result = input_left_align(title, dst, CONTACT_FIELD_MAX_WIDTH);

	if (result == EOF || result == FAILURE) {
		return result;
	}
	if (dst.empty()) {
		std::cerr << MSG_EMPTY_CONTACT_INFO << std::endl;
		return FAILURE;
	}
	return (SUCCESS);
}

static t_result input_data(t_contact_dto &data) {
	t_pair fields[] = {
		{FIRST_NAME, data.first_name},
		{LAST_NAME, data.last_name},
		{NICK_NAME, data.nick_name},
		{PHONE_NUMBER, data.phone_number},
		{DARKEST_SECRET, data.darkest_secret}
	};
	const size_t size = sizeof(fields) / sizeof(fields[0]);

	for (size_t i = 0; i < size; i++) {
		t_result result = input_each_data(fields[i].title, fields[i].dst);
		if (result == EOF || result == FAILURE) {
			return result;
		}
	}
	return SUCCESS;
}

static void convert_data_to_contact(Contact &contact, const t_contact_dto &data) {
	contact = Contact(data);
}

static t_result input_contact_date(Contact &contact) {
	t_contact_dto  data;
	const t_result result = input_data(data);

	if (result == EOF || result == FAILURE) {
		return result;
	}
	convert_data_to_contact(contact, data);
	return SUCCESS;
}

void exec_add(Phonebook &phonebook) {
	Contact        contact;
	const t_result result = input_contact_date(contact);

	if (result == EOF) {
		return;
	}
	if (result == FAILURE) {
		std::cerr << MSG_SAVE_FAIL << std::endl;
		return;
	}
	phonebook.save_contact(contact);
	std::cerr << MSG_SAVE_SUCCESS << std::endl;
}

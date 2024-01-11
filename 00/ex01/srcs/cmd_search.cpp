#include "command.hpp"
#include "phonebook.hpp"
#include "utils.hpp"
#include <iostream>

static unsigned int input_index_of_entry(t_result &result) {
	unsigned int index_of_contact = 0;

	result = input_left_align(MSG_SEARCH, index_of_contact, SEARCH_INPUT_WIDTH);
	return index_of_contact;
}

static void display_contact_by_index(const Phonebook &phonebook) {
	t_result           result           = SUCCESS;
	const unsigned int index_of_contact = input_index_of_entry(result);

	if (result == FAILURE) {
		std::cerr << MSG_RETRY_INPUT_INDEX << std::endl;
		return;
	}
	if (!phonebook.is_valid_index(index_of_contact)) {
		std::cerr << MSG_RETRY_INPUT_INDEX << std::endl;
		return;
	}
	phonebook.display_contact_detail_by_index(index_of_contact);
}

void exec_search(const Phonebook &phonebook) {
	phonebook.display_all();
	display_contact_by_index(phonebook);
}

#include "color.hpp"
#include "command.hpp"
#include "io.hpp"
#include "phonebook.hpp"
#include <iostream>

static t_result input_positive_integer(unsigned int &index_of_contact) {
	int            tmp_num = 0;
	const t_result result =
		input_left_align(MSG_SEARCH, tmp_num, SEARCH_INPUT_WIDTH);

	if (result == INPUT_EOF) {
		std::cout << std::endl;
		return INPUT_EOF;
	}
	if (result == FAILURE || tmp_num < 0) {
		put_error(MSG_RETRY_INPUT_INDEX);
		return FAILURE;
	}
	index_of_contact = static_cast<unsigned int>(tmp_num);
	return SUCCESS;
}

static unsigned int input_index_of_entry(t_result &result) {
	unsigned int index_of_contact = 0;

	result = input_positive_integer(index_of_contact);
	return index_of_contact;
}

static void display_contact_by_index(const Phonebook &phonebook) {
	t_result           result           = SUCCESS;
	const unsigned int index_of_contact = input_index_of_entry(result);

	if (result == INPUT_EOF || result == FAILURE) {
		return;
	}
	if (!phonebook.is_valid_index(index_of_contact)) {
		put_error(MSG_RETRY_INPUT_INDEX);
		return;
	}
	phonebook.display_contact_detail_by_index(index_of_contact);
}

void exec_search(const Phonebook &phonebook) {
	phonebook.display_all();
	display_contact_by_index(phonebook);
}

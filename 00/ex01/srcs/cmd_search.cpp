#include "command.hpp"
#include "phonebook.hpp"
#include "utils.hpp"

static unsigned int input_index_of_entry() {
	unsigned int index_of_contact = 0;

	input_left_align(MSG_SEARCH, index_of_contact, SEARCH_INPUT_WIDTH);
	return index_of_contact;
}

void exec_search(Phonebook &phonebook) {
	phonebook.display_all();
	const unsigned int index_of_contact = input_index_of_entry();
	// todo: display all contact fields
}

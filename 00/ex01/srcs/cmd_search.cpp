#include "command.hpp"
#include "phonebook.hpp"
#include "utils.hpp"

static unsigned int input_index_of_entry() {
	unsigned int index_of_contact = 0;

	input_left_align(MSG_SEARCH, index_of_contact, SEARCH_INPUT_WIDTH);
	return index_of_contact;
}

static void display_contact_by_index(const Phonebook &phonebook) {
	const unsigned int index_of_contact = input_index_of_entry();

	phonebook.display_contact_detail_by_index(index_of_contact);
}

void exec_search(const Phonebook &phonebook) {
	phonebook.display_all();
	display_contact_by_index(phonebook);
}

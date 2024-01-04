#include "command.hpp"
#include "contact.hpp"
#include "phonebook.hpp"
#include <cstdlib>
#include <iostream>

static t_command set_command(const std::string &command) {
	t_command ret;

	if (command == STR_ADD) {
		ret = CMD_ADD;
	} else if (command == STR_EARCH) {
		ret = CMD_SEARCH;
	} else if (command == STR_EXIT) {
		ret = CMD_EXIT;
	} else {
		ret = CMD_INVALID;
	}
	return ret;
}

int main(void) {
	t_command command = CMD_INVALID;
	t_contact data;
	Contact   contact;
	Phonebook phonebook;

	while (command != CMD_EXIT) {
		std::cout << "----------------------------------------" << std::endl
				  << " Enter one of the commands below:" << std::endl
				  << "  - ADD    : save a new contact" << std::endl
				  << "  - SEARCH : display a specific contact" << std::endl
				  << "  - EXIT   : exit the program" << std::endl
				  << "----------------------------------------" << std::endl;

		std::string input;
		std::cin >> input;

		command = set_command(input);
		switch (command) {
		case CMD_ADD:
			input_contact_date(data);
			contact = Contact(data);
			phonebook.save_contact(contact);
			phonebook.print_phonebook_all();
			break;
		case CMD_SEARCH:
			// todo: impl search
			std::cout << input << std::endl;
			break;
		case CMD_EXIT:
			// todo: impl exit
			std::cout << input << std::endl;
			break;
		default:
			break;
		}
	}
	return EXIT_SUCCESS;
}

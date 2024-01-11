#include "command.hpp"
#include "phonebook.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

static void display_command_guide() {
	std::cout << std::endl
			  << "----------------------------------------" << std::endl
			  << " Enter one of the commands below:" << std::endl
			  << "  - ADD    : save a new contact" << std::endl
			  << "  - SEARCH : display a specific contact" << std::endl
			  << "  - EXIT   : exit the program" << std::endl
			  << "----------------------------------------" << std::endl
			  << ">> ";
}

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
	Phonebook phonebook;

	while (command != CMD_EXIT) {
		display_command_guide();

		std::string input;
		std::cin >> input;

		command = set_command(input);
		switch (command) {
		case CMD_ADD:
			exec_add(phonebook);
			break;
		case CMD_SEARCH:
			exec_search(phonebook);
			break;
		case CMD_EXIT:
			break;
		default:
			break;
		}
	}
	return EXIT_SUCCESS;
}

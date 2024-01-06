#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "phonebook.hpp"

/* command */
#define STR_ADD "ADD"
#define STR_EARCH "SEARCH"
#define STR_EXIT "EXIT"

/* SEARCH */
#define SEARCH_INPUT_WIDTH 0
#define MSG_SEARCH         "Enter the index of the contact to display details"

typedef enum e_command {
	CMD_ADD,
	CMD_SEARCH,
	CMD_EXIT,
	CMD_INVALID,
} t_command;

void exec_add(Phonebook &phonebook);
void exec_search(Phonebook &phonebook);

#endif

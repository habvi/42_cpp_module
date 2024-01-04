#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "phonebook.hpp"

#define STR_ADD "ADD"
#define STR_EARCH "SEARCH"
#define STR_EXIT "EXIT"

typedef enum e_command {
	CMD_ADD,
	CMD_SEARCH,
	CMD_EXIT,
	CMD_INVALID,
} t_command;

void exec_add(Phonebook &phonebook);

#endif

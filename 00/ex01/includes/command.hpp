#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "phonebook.hpp"

/* command */
#define STR_ADD "ADD"
#define STR_EARCH "SEARCH"
#define STR_EXIT "EXIT"

/* ADD */
#define INPUT_WIDTH 15

#define FIRST_NAME "first name"
#define LAST_NAME "last name"
#define NICK_NAME "nickname"
#define PHONE_NUMBER "phone number"
#define DARKEST_SECRET "darkest secret"

typedef enum e_command {
	CMD_ADD,
	CMD_SEARCH,
	CMD_EXIT,
	CMD_INVALID,
} t_command;

void exec_add(Phonebook &phonebook);
void exec_search(Phonebook &phonebook);

#endif

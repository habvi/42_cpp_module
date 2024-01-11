#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "phonebook.hpp"

/* command */
#define STR_ADD   "ADD"
#define STR_EARCH "SEARCH"
#define STR_EXIT  "EXIT"

/* ADD */
#define MSG_SAVE_SUCCESS "ADD Success!"

/* SEARCH */
#define SEARCH_INPUT_WIDTH 0
#define MSG_SEARCH         "Enter the index of the contact to display details"
#define MSG_RETRY_INPUT_INDEX                                                       \
	"Error: Invalid index. Please enter the registerd contact index."

typedef enum e_command {
	CMD_ADD,
	CMD_SEARCH,
	CMD_EXIT,
	CMD_INVALID,
} t_command;

void exec_add(Phonebook &phonebook);
void exec_search(const Phonebook &phonebook);

#endif

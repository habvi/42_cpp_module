#ifndef __PHONEBOOK_H__
#define __PHONEBOOK_H__

#include "contact.hpp"

#define LIMIT_REGISTER_COUNT 8
#define COLUMN_WIDTH         10
#define TRUNCATED_LAST_CHAR  '.'
#define MSG_INVALID_INDEX                                                           \
	"Error: Invalid index. Please enter a value within the range 0-7."

class Phonebook {
  public:
	Phonebook();
	~Phonebook();

  public:
	void save_contact(const Contact &contact);
	void display_all() const;
	void display_contact_detail_by_index(const unsigned int index_of_contact) const;

  private:
	Contact phonebook_[LIMIT_REGISTER_COUNT];
};

#endif /*__PHONEBOOK_H__*/

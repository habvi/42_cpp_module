#ifndef __PHONEBOOK_H__
#define __PHONEBOOK_H__

#include "contact.hpp"

#define LIMIT_REGISTER_COUNT 8

class Phonebook {
  public:
	Phonebook();
	~Phonebook();

  public:
	void save_contact(const Contact &contact);

  private:
	Contact phonebook_[LIMIT_REGISTER_COUNT];
};

#endif /*__PHONEBOOK_H__*/

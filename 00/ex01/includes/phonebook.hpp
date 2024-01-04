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
	void display_all();

  private:
	void display_name_data_in_contact_(const unsigned int index);
	void display_specific_contact_(const unsigned int index);

  private:
	Contact phonebook_[LIMIT_REGISTER_COUNT];
};

#endif /*__PHONEBOOK_H__*/

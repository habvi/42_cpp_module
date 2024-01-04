#ifndef __CONTACT_H__
#define __CONTACT_H__

#include <string>

typedef struct s_contact {
	std::string first_name;
	std::string last_name;
	std::string nick_name;
	std::string phone_number;
	std::string darkest_secret;
} t_contact;

class Contact {
  public:
	Contact();
	explicit Contact(const t_contact &data);
	~Contact();

	// destructor

  private:
	std::string first_name_;
	std::string last_name_;
	std::string nick_name_;
	std::string phone_number_;
	std::string darkest_secret_;
};

#endif /*__CONTACT_H__*/
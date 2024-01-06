#ifndef __CONTACT_H__
#define __CONTACT_H__

#include <string>

// field title
#define FIRST_NAME     "First Name"
#define LAST_NAME      "Last Name"
#define NICK_NAME      "Nickname"
#define PHONE_NUMBER   "Phone Number"
#define DARKEST_SECRET "Darkest Secret"

// display
#define CONTACT_FIELD_MAX_WIDTH 15

typedef struct s_contact_dto {
	std::string first_name;
	std::string last_name;
	std::string nick_name;
	std::string phone_number;
	std::string darkest_secret;
} t_contact_dto;

class Contact {
  public:
	Contact();
	explicit Contact(const t_contact_dto &data);
	~Contact();

  public:
	const std::string first_name() const;
	const std::string last_name() const;
	const std::string nick_name() const;

  private:
	std::string first_name_;
	std::string last_name_;
	std::string nick_name_;
	std::string phone_number_;
	std::string darkest_secret_;
};

#endif /*__CONTACT_H__*/

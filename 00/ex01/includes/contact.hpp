#ifndef __CONTACT_H__
#define __CONTACT_H__

#include <string>

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
	std::string first_name() const;
	std::string last_name() const;
	std::string nick_name() const;

  private:
	std::string first_name_;
	std::string last_name_;
	std::string nick_name_;
	std::string phone_number_;
	std::string darkest_secret_;
};

void input_contact_date(Contact &contact);

#endif /*__CONTACT_H__*/
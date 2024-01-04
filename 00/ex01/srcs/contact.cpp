#include "contact.hpp"

Contact::Contact() {}

Contact::Contact(const t_contact &data) {
	// todo: throw error with empty contact member?
	first_name_     = data.first_name;
	last_name_      = data.last_name;
	nick_name_      = data.nick_name;
	phone_number_   = data.phone_number;
	darkest_secret_ = data.darkest_secret;
}

Contact::~Contact() {}


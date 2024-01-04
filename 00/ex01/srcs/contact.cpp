#include "contact.hpp"

Contact::Contact() {}

Contact::Contact(const t_contact_dto &data) {
	first_name_     = data.first_name;
	last_name_      = data.last_name;
	nick_name_      = data.nick_name;
	phone_number_   = data.phone_number;
	darkest_secret_ = data.darkest_secret;
}

Contact::~Contact() {}

const std::string Contact::first_name() const {
	return first_name_;
}

const std::string Contact::last_name() const {
	return last_name_;
}

const std::string Contact::nick_name() const {
	return nick_name_;
}

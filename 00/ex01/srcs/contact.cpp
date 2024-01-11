#include "contact.hpp"
#include "utils.hpp"
#include <string>

Contact::Contact() {}

Contact::Contact(const t_contact_dto &data) {
	first_name_     = data.first_name;
	last_name_      = data.last_name;
	nick_name_      = data.nick_name;
	phone_number_   = data.phone_number;
	darkest_secret_ = data.darkest_secret;
}

Contact::~Contact() {}

// It's not necessary to implement this explicitly. they are handled automatically.
Contact::Contact(const Contact &c) {
	first_name_     = c.first_name_;
	last_name_      = c.last_name_;
	nick_name_      = c.nick_name_;
	phone_number_   = c.phone_number_;
	darkest_secret_ = c.darkest_secret_;
}

// It's not necessary to implement this explicitly. they are handled automatically.
const Contact &Contact::operator=(const Contact &c) {
	if (this != &c) {
		first_name_     = c.first_name_;
		last_name_      = c.last_name_;
		nick_name_      = c.nick_name_;
		phone_number_   = c.phone_number_;
		darkest_secret_ = c.darkest_secret_;
	}
	return *this;
}

const std::string Contact::get_first_name() const {
	return first_name_;
}

const std::string Contact::get_last_name() const {
	return last_name_;
}

const std::string Contact::get_nick_name() const {
	return nick_name_;
}

void Contact::display_all() const {
	static const int output_width = CONTACT_FIELD_MAX_WIDTH;

	output_left_align(FIRST_NAME, first_name_, output_width);
	output_left_align(LAST_NAME, last_name_, output_width);
	output_left_align(NICK_NAME, nick_name_, output_width);
	output_left_align(PHONE_NUMBER, phone_number_, output_width);
	output_left_align(DARKEST_SECRET, darkest_secret_, output_width);
}

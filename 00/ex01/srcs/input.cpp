#include "contact.hpp"
#include <iostream>

// todo: not allow empty input
static t_contact input_data() {
	t_contact data;

	std::cout << "fitst name     : ";
	std::cin >> data.first_name;
	std::cout << "last name      : ";
	std::cin >> data.last_name;
	std::cout << "nickname       : ";
	std::cin >> data.nick_name;
	std::cout << "phone number   : ";
	std::cin >> data.phone_number;
	std::cout << "darkest secret : ";
	std::cin >> data.darkest_secret;
	return data;
}

static void convert_data_to_contact(Contact &contact, const t_contact &data) {
	contact = Contact(data);
}

void input_contact_date(Contact &contact) {
	const t_contact data = input_data();

	convert_data_to_contact(contact, data);
}

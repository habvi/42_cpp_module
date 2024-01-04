#include "contact.hpp"
#include <iostream>

void input_contact_date(t_contact &data) {
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
}

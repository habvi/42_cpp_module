#include "Harl.hpp"
#include <iostream>
#include <string>

Harl::Harl() {}

Harl::~Harl() {}

static void PutError(const std::string &message) {
	std::cout << COLOR_RED << "Error: " << message << COLOR_END << std::endl;
}

typedef std::pair<std::string, void (Harl::*)()> Pair;

void Harl::complain(std::string level) {
	static const Pair complains[] = {
		std::make_pair(DEBUG, &Harl::debug),
		std::make_pair(INFO, &Harl::info),
		std::make_pair(WARNING, &Harl::warning),
		std::make_pair(ERROR, &Harl::error)
	};
	size_t size = sizeof(complains) / sizeof(complains[0]);

	for (size_t i = 0; i < size; i++) {
		if (complains[i].first == level) {
			(this->*(complains[i].second))();
			return;
		}
	}
	PutError(ERR_INVALID_LEVEL);
}

static void Put(const std::string &message) {
	std::cout << message << std::endl;
}

void Harl::debug(void) {
	Put("I love having extra bacon for my "
		"7XL-double-cheese-triple-pickle-specialketchup burger. I really do!");
}

void Harl::info(void) {
	Put("I cannot believe adding extra bacon costs more money. You didn’t Put "
		"enough bacon in my burger! If you did, I wouldn’t be asking for more!");
}

void Harl::warning(void) {
	Put("I think I deserve to have some extra bacon for free. I’ve been coming for "
		"years whereas you started working here since last month.");
}

void Harl::error(void) {
	Put("This is unacceptable! I want to speak to the manager now.");
}

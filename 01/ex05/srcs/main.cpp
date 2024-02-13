#include "Harl.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

static void Put(const std::string &level) {
	std::cout << std::endl << COLOR_GREEN << level << COLOR_END << std::endl;
}

int main() {
	Harl harl_1;

	/* normal case */
	Put("DEBUG");
	harl_1.complain(DEBUG);
	Put("INFO");
	harl_1.complain(INFO);
	Put("WARNING");
	harl_1.complain(WARNING);
	Put("ERROR");
	harl_1.complain(ERROR);
	Put("INFO");
	harl_1.complain(INFO);
	Put("WARNING");
	harl_1.complain(WARNING);

	/* error case */
	Put("NOT EXIST");
	harl_1.complain("not_exist");
	Put("EMPTY");
	harl_1.complain("");

	// -----------------------------------
	Harl harl_2;

	/* normal case */
	Put("DEBUG");
	harl_2.complain(DEBUG);
	Put("ERROR");
	harl_2.complain(ERROR);

	/* error case */
	Put("EMPTY");
	harl_2.complain("");
	Put("NOT EXIST");
	harl_2.complain("not_exist");

	return EXIT_SUCCESS;
}

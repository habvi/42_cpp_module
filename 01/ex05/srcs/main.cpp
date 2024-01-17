#include "Harl.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

static void put(const std::string &level) {
	std::cout << std::endl << COLOR_GREEN << level << COLOR_END << std::endl;
}

int main() {
	Harl harl_1;

	/* normal case */
	put("DEBUG");
	harl_1.complain(DEBUG);
	put("INFO");
	harl_1.complain(INFO);
	put("WARNING");
	harl_1.complain(WARNING);
	put("ERROR");
	harl_1.complain(ERROR);
	put("INFO");
	harl_1.complain(INFO);
	put("WARNING");
	harl_1.complain(WARNING);

	/* error case */
	put("NOT EXIST");
	harl_1.complain("not_exist");
	put("EMPTY");
	harl_1.complain("");

	// -----------------------------------
	Harl harl_2;

	/* normal case */
	put("DEBUG");
	harl_2.complain(DEBUG);
	put("ERROR");
	harl_2.complain(ERROR);

	/* error case */
	put("EMPTY");
	harl_2.complain("");
	put("NOT EXIST");
	harl_2.complain("not_exist");

	return EXIT_SUCCESS;
}

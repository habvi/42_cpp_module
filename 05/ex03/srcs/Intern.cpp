#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "color.hpp"
#include <iostream>
#include <new>

Intern::Intern() {}

Intern::Intern(const Intern &i) {
	(void)i;
}

const Intern &Intern::operator=(const Intern &i) {
	(void)i;
	return *this;
}

Intern::~Intern() {}

AForm *TryMakeForm(const std::string &form_name, const std::string &target) {
	AForm *form = NULL;

	// todo: don't use if/else
	if (form_name == "presidential pardon") {
		form = new (std::nothrow) PresidentialPardonForm(target);
	} else if (form_name == "robotomy request") {
		form = new (std::nothrow) RobotomyRequestForm(target);
	} else if (form_name == "shrubbery creation") {
		form = new (std::nothrow) ShrubberyCreationForm(target);
	} else {
		throw std::logic_error("Error: invalid Form name");
	}
	if (form == NULL) {
		throw;
	}
	return form;
}

AForm *Intern::makeForm(const std::string &form_name, const std::string &target) {
	AForm *form;

	try {
		form = TryMakeForm(form_name, target);
		std::cout << COLOR_PINK "Intern creats " << form_name << COLOR_END
				  << std::endl;
	} catch (const std::exception &e) {
		std::cerr << COLOR_PINK << "Intern creats Form failed. => " COLOR_RED
				  << e.what() << COLOR_END << std::endl;
		return NULL;
	}
	return form;
}

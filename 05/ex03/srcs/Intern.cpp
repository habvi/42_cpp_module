#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "color.hpp"
#include "form_list.hpp"
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

static AForm *CreatePresidentialPardonForm(const std::string &target) {
	return new PresidentialPardonForm(target);
}

static AForm *CreateRobotomyRequestForm(const std::string &target) {
	return new RobotomyRequestForm(target);
}

static AForm *CreateShrubberyCreationForm(const std::string &target) {
	return new ShrubberyCreationForm(target);
}

typedef AForm *(*CreateFormFunc)(const std::string &);
typedef std::pair<const std::string, CreateFormFunc> FormPair;

static CreateFormFunc GetCreateFormFunction(const std::string &form_name) {
	static const FormPair forms[] = {
		std::make_pair(kPresidentialPardonFormName, &CreatePresidentialPardonForm),
		std::make_pair(kRobotomyRequestFormName, &CreateRobotomyRequestForm),
		std::make_pair(kShrubberyCreationFormName, &CreateShrubberyCreationForm)
	};
	const size_t size = sizeof(forms) / sizeof(forms[0]);

	for (size_t i = 0; i < size; i++) {
		if (forms[i].first == form_name) {
			return forms[i].second;
		}
	}
	return NULL;
}

static AForm *TryMakeForm(const std::string &form_name, const std::string &target) {
	CreateFormFunc create_form = GetCreateFormFunction(form_name);
	if (create_form == NULL) {
		throw std::logic_error("Error: invalid Form name");
	}
	return create_form(target);
}

AForm *
Intern::makeForm(const std::string &form_name, const std::string &target) const {
	AForm *form = NULL;

	try {
		form = TryMakeForm(form_name, target);
		std::cout << COLOR_PINK "Intern creates " << form_name << COLOR_END
				  << std::endl;
	} catch (const std::exception &e) {
		std::cerr << COLOR_PINK << "Intern creates Form failed. => " COLOR_RED
				  << e.what() << COLOR_END << std::endl;
		return NULL;
	}
	return form;
}

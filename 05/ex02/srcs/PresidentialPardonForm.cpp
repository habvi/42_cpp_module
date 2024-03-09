#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"
#include "color.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm() {}

PresidentialPardonForm::PresidentialPardonForm(const std::string &name)
	: AForm(name, kGradeForSign, kGradeForExecute) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &p)
	: AForm(p.GetName(), p.GetGradeForSign(), p.GetGradeForExecute()) {}

const PresidentialPardonForm &
PresidentialPardonForm::operator=(const PresidentialPardonForm &p) {
	if (this != &p) {
		AForm::operator=(p);
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const {
	try {
		AForm::execute(executor);
	} catch (const std::exception &e) {
		throw;
	}
	std::cout << "executor(" COLOR_BLUE << executor.getName()
			  << COLOR_END "): target(" << COLOR_BLUE << GetName()
			  << COLOR_END ") has been pardoned by Zaphod Beeblebrox." COLOR_END
			  << std::endl;
}

#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"
#include "color.hpp"
#include <iostream>

const std::string PresidentialPardonForm::kFormName = "Presidential Pardon";

PresidentialPardonForm::PresidentialPardonForm() {}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
	: AForm(kFormName, kGradeForSign, kGradeForExecute), target_(target) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &p)
	: AForm(p.GetName(), p.GetGradeForSign(), p.GetGradeForExecute()),
	  target_(p.GetTarget()) {}

const PresidentialPardonForm &
PresidentialPardonForm::operator=(const PresidentialPardonForm &p) {
	if (this != &p) {
		AForm::operator=(p);
		target_ = p.GetTarget();
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {}

const std::string &PresidentialPardonForm::GetTarget() const {
	return target_;
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const {
	try {
		AForm::execute(executor);
	} catch (const std::exception &e) {
		throw;
	}
	std::cout << "executor(" COLOR_BLUE << executor.getName()
			  << COLOR_END "): target(" << COLOR_BLUE << GetTarget()
			  << COLOR_END ") has been pardoned by Zaphod Beeblebrox." << std::endl;
}

#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include "color.hpp"
#include <iostream>

const std::string ShrubberyCreationForm::kFormName = "Shrubbery Creation";

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm(kFormName, kGradeForSign, kGradeForExecute), target_(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &s)
	: AForm(s.GetName(), s.GetGradeForSign(), s.GetGradeForExecute()),
	  target_(s.GetTarget()) {}

const ShrubberyCreationForm &
ShrubberyCreationForm::operator=(const ShrubberyCreationForm &s) {
	if (this != &s) {
		AForm::operator=(s);
		target_ = s.GetTarget();
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

const std::string &ShrubberyCreationForm::GetTarget() const {
	return target_;
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
	try {
		AForm::execute(executor);
	} catch (const std::exception &e) {
		throw;
	}
	// todo
	std::cout << "executor(" COLOR_BLUE << executor.getName()
			  << COLOR_END "): target(" << COLOR_BLUE << GetTarget()
			  << COLOR_END ") write tree to file." COLOR_END << std::endl;
}

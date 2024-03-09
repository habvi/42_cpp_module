#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include "color.hpp"
#include <iostream>

const std::string RobotomyRequestForm::kFormName = "Robotomy Request";

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
	: AForm(kFormName, kGradeForSign, kGradeForExecute), target_(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &r)
	: AForm(r.GetName(), r.GetGradeForSign(), r.GetGradeForExecute()),
	  target_(r.GetTarget()) {}

const RobotomyRequestForm &
RobotomyRequestForm::operator=(const RobotomyRequestForm &r) {
	if (this != &r) {
		AForm::operator=(r);
		target_ = r.GetTarget();
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

const std::string &RobotomyRequestForm::GetTarget() const {
	return target_;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
	try {
		AForm::execute(executor);
	} catch (const std::exception &e) {
		throw;
	}
	// todo
	std::cout << "executor(" COLOR_BLUE << executor.getName()
			  << COLOR_END "): target(" << COLOR_BLUE << GetTarget()
			  << COLOR_END ") robotomized or not" COLOR_END << std::endl;
}

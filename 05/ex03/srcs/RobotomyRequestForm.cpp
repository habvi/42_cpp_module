#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include "color.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

const std::string RobotomyRequestForm::kFormName = "Robotomy Request";

RobotomyRequestForm::RobotomyRequestForm() {}

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

static bool IsRobotomized() {
	std::srand(std::time(NULL));
	const unsigned int  random_int = std::rand();
	static unsigned int number     = random_int % 2;

	number ^= 1;
	return number == 1;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
	AForm::execute(executor);
}

// override
void RobotomyRequestForm::ExecuteEachForm(Bureaucrat const &executor) const {
	std::cout << "Drrrrrrrrrrrrrrr...." << std::endl;
	std::cout << "executor(" COLOR_BLUE << executor.getName()
			  << COLOR_END "): target(" << COLOR_BLUE << GetTarget()
			  << COLOR_END ")";
	if (IsRobotomized()) {
		std::cout << " has been robotomized successfully." << std::endl;
	} else {
		std::cout << " Failed to robotomized." << std::endl;
	}
}

#ifndef EX02_ROBOTOMY_REQUEST_FORM_HPP
#define EX02_ROBOTOMY_REQUEST_FORM_HPP

#include "AForm.hpp"
#include <string>

class Bureaucrat;

class RobotomyRequestForm : public AForm {
  public:
	explicit RobotomyRequestForm(const std::string &target);
	RobotomyRequestForm(const RobotomyRequestForm &r);
	const RobotomyRequestForm &operator=(const RobotomyRequestForm &r);
	~RobotomyRequestForm();

  public:
	const std::string &GetTarget() const;

  public:
	// Following the instructions, not camelcase
	void execute(Bureaucrat const &executor) const;

  private:
	RobotomyRequestForm();

  private:
	void ExecuteEachForm(Bureaucrat const &executor) const;

  private:
	static const std::string  kFormName;
	static const unsigned int kGradeForSign    = 72;
	static const unsigned int kGradeForExecute = 45;
	std::string               target_;
};

#endif /* EX02_ROBOTOMY_REQUEST_FORM_HPP */

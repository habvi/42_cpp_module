#ifndef EX01_FORM_HPP
#define EX01_FORM_HPP

#include <ostream>
#include <string>

class Bureaucrat;

class Form {
  public:
	Form(
		const std::string &name,
		const unsigned int grade_for_sign,
		const unsigned int grade_for_execute
	);
	Form(const Form &f);
	~Form();
	const Form &operator=(const Form &f);

  public:
	const std::string &GetName() const;
	bool               GetIsSigned() const;
	unsigned int       GetGradeForSign() const;
	unsigned int       GetGradeForExecute() const;
	// Following the instructions, not camelcase
	bool beSigned(const Bureaucrat &b);

  private:
	Form();
	const char *GradeTooHighException() const;
	const char *GradeTooLowException() const;

  private:
	static const unsigned int kHighestGrade = 1;
	static const unsigned int kLowestGrade  = 150;
	const std::string         name_;
	bool                      is_signed_;
	const unsigned int        grade_for_sign_;
	const unsigned int        grade_for_execute_;
};

std::ostream &operator<<(std::ostream &out, const Form &b);

#endif
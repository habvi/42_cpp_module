#ifndef EX02_AFORM_HPP
#define EX02_AFORM_HPP

#include <ostream>
#include <string>

class Bureaucrat;

class AForm {
  public:
	AForm(
		const std::string &name,
		const unsigned int grade_for_sign,
		const unsigned int grade_for_execute
	);
	AForm(const AForm &f);
	virtual ~AForm();
	const AForm &operator=(const AForm &f);

  public:
	const std::string &GetName() const;
	bool               GetIsSigned() const;
	unsigned int       GetGradeForSign() const;
	unsigned int       GetGradeForExecute() const;
	// Following the instructions, not camelcase
	bool beSigned(const Bureaucrat &b);

  private:
	AForm();
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

std::ostream &operator<<(std::ostream &out, const AForm &b);

#endif /* EX02_AFORM_HPP */

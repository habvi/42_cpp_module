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

  private:
	void ThrowGradeException(const unsigned int grade) const;
	void GradeTooHighException() const;
	void GradeTooLowException() const;

  private:
	const std::string  name_;
	bool               is_signed_;
	const unsigned int grade_for_sign_;
	const unsigned int grade_for_execute_;
};

std::ostream &operator<<(std::ostream &out, const Form &b);

#endif

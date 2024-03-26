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

  public:
	// Following the instructions, not camelcase
	void         beSigned(const Bureaucrat &b);
	virtual void execute(Bureaucrat const &executor) const;

  protected:
	AForm();

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

std::ostream &operator<<(std::ostream &out, const AForm &b);

#endif /* EX02_AFORM_HPP */

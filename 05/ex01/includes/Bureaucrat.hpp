#ifndef EX01_BUREAUCRAT_HPP
#define EX01_BUREAUCRAT_HPP

#include <ostream>
#include <stdexcept> // logic_error
#include <string>

class Form;

class Bureaucrat {
  public:
	Bureaucrat(const std::string &name, const unsigned int grade);
	Bureaucrat(const Bureaucrat &b);
	~Bureaucrat();
	const Bureaucrat &operator=(const Bureaucrat &b);

  public:
	// Following the instructions,
	// exception classes don’t have to be designed in Orthodox Canonical Form.
	class GradeTooHighException : public std::logic_error {
	  public:
		GradeTooHighException();
	};
	class GradeTooLowException : public std::logic_error {
	  public:
		GradeTooLowException();
	};

  public:
	// Following the instructions, not camelcase
	const std::string  &getName() const;
	unsigned int        getGrade() const;
	static unsigned int GetHighestGrade();
	static unsigned int GetLowestGrade();

  public:
	void IncrementGrade();
	void DecrementGrade();
	// Following the instructions, not camelcase
	void signForm(Form &form) const;

  private:
	Bureaucrat();

  private:
	void ThrowGradeException(const unsigned int grade) const;

  private:
	static const unsigned int kHighestGrade = 1;
	static const unsigned int kLowestGrade  = 150;
	const std::string         name_;
	unsigned int              grade_;
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &b);

#endif /* EX01_BUREAUCRAT_HPP */

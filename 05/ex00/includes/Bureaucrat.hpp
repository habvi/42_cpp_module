#ifndef EX00_BUREAUCRAT_HPP
#define EX00_BUREAUCRAT_HPP

#include <ostream>
#include <string>

class Bureaucrat {
  public:
	Bureaucrat(const std::string &name, const unsigned int grade);
	Bureaucrat(const Bureaucrat &b);
	~Bureaucrat();
	const Bureaucrat &operator=(const Bureaucrat &b);

  public:
	// Following the instructions, not camelcase
	const std::string &getName() const;
	unsigned int       getGrade() const;

  public:
	void IncrementGrade();
	void DecrementGrade();

  private:
	Bureaucrat();
	const char *GradeTooHighException() const;
	const char *GradeTooLowException() const;

  private:
	static const unsigned int kHighestGrade = 1;
	static const unsigned int kLowestGrade  = 150;
	const std::string         name_;
	unsigned int              grade_;
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &b);

#endif /* EX00_BUREAUCRAT_HPP */

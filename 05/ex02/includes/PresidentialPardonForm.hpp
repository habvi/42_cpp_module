#ifndef EX02_PRESIDENTIAL_PARDON_FORM_HPP
#define EX02_PRESIDENTIAL_PARDON_FORM_HPP

#include "AForm.hpp"
#include <string>

class Bureaucrat;

class PresidentialPardonForm : public AForm {
  public:
	explicit PresidentialPardonForm(const std::string &name);
	PresidentialPardonForm(const PresidentialPardonForm &p);
	const PresidentialPardonForm &operator=(const PresidentialPardonForm &p);
	~PresidentialPardonForm();

  public:
	void execute(Bureaucrat const &executor) const;

  private:
	PresidentialPardonForm();

  private:
	static const unsigned int kGradeForSign    = 25;
	static const unsigned int kGradeForExecute = 5;
};

#endif /* EX02_PRESIDENTIAL_PARDON_FORM_HPP */

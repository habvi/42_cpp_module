#ifndef EX02_SHRUBBERY_CREATION_FORM_HPP
#define EX02_SHRUBBERY_CREATION_FORM_HPP

#include "AForm.hpp"
#include <string>

class Bureaucrat;

class ShrubberyCreationForm : public AForm {
  public:
	explicit ShrubberyCreationForm(const std::string &target);
	ShrubberyCreationForm(const ShrubberyCreationForm &s);
	const ShrubberyCreationForm &operator=(const ShrubberyCreationForm &s);
	~ShrubberyCreationForm();

  public:
	const std::string &GetTarget() const;

  public:
	void execute(Bureaucrat const &executor) const;

  private:
	void WriteTreeToFile() const;

  private:
	static const std::string  kFormName;
	static const unsigned int kGradeForSign    = 145;
	static const unsigned int kGradeForExecute = 137;
	static const std::string  kFileSuffix;
	std::string               target_;
};

#endif /* EX02_SHRUBBERY_CREATION_FORM_HPP */

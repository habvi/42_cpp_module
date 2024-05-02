#ifndef EX03_INTERN_FORM_HPP
#define EX03_INTERN_FORM_HPP

#include <string>

class AForm;

class Intern {
  public:
	Intern();
	Intern(const Intern &i);
	Intern &operator=(const Intern &i);
	~Intern();

  public:
	// Following the instructions, not camelcase
	AForm *makeForm(const std::string &form_name, const std::string &target) const;
};

#endif /* EX03_INTERN_FORM_HPP */

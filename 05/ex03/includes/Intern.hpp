#ifndef EX03_INTERN_FORM_HPP
#define EX03_INTERN_FORM_HPP

#include <string>

class AForm;

class Intern {
  public:
	Intern();
	Intern(const Intern &i);
	const Intern &operator=(const Intern &i);
	~Intern();

  public:
	AForm *makeForm(const std::string &form_name, const std::string &target);
};

#endif /* EX03_INTERN_FORM_HPP */

#ifndef EX01_FORM_HPP
#define EX01_FORM_HPP

#include <string>

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

  private:
	Form();
	static const unsigned int kLowestGrade  = 150;
	const std::string         name_;
	bool                      is_signed_;
	const unsigned int        grade_for_sign_;
	const unsigned int        grade_for_execute_;
};

#endif

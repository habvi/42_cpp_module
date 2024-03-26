#include "Form.hpp"
#include "Bureaucrat.hpp"
#include "color.hpp"

Form::Form() : grade_for_sign_(kLowestGrade), grade_for_execute_(kLowestGrade) {}

Form::Form(
	const std::string &name,
	const unsigned int grade_for_sign,
	const unsigned int grade_for_execute
)
	: name_(name),
	  is_signed_(false),
	  grade_for_sign_(grade_for_sign),
	  grade_for_execute_(grade_for_execute) {
	ThrowGradeException(grade_for_sign);
	ThrowGradeException(grade_for_execute);
}

Form::Form(const Form &f)
	: name_(f.GetName()),
	  is_signed_(f.GetIsSigned()),
	  grade_for_sign_(f.GetGradeForSign()),
	  grade_for_execute_(f.GetGradeForExecute()) {}

Form::~Form() {}

const Form &Form::operator=(const Form &f) {
	if (this != &f) {
		is_signed_ = f.GetIsSigned();
	}
	return *this;
}

const std::string &Form::GetName() const {
	return name_;
}

bool Form::GetIsSigned() const {
	return is_signed_;
}

unsigned int Form::GetGradeForSign() const {
	return grade_for_sign_;
}

unsigned int Form::GetGradeForExecute() const {
	return grade_for_execute_;
}

bool Form::beSigned(const Bureaucrat &b) {
	if (b.getGrade() > kLowestGrade) {
		throw GradeTooLowException();
	}
	if (b.getGrade() <= grade_for_sign_) {
		is_signed_ = true;
		return true;
	}
	return false;
}

void Form::ThrowGradeException(const unsigned int grade) const {
	if (grade < Bureaucrat::GetHighestGrade()) {
		Form::GradeTooHighException();
	} else if (grade > Bureaucrat::GetLowestGrade()) {
		Form::GradeTooLowException();
	}
}

void Form::GradeTooHighException() const {
	throw Bureaucrat::GradeTooHighException();
}

void Form::GradeTooLowException() const {
	throw Bureaucrat::GradeTooLowException();
}

std::ostream &operator<<(std::ostream &out, const Form &f) {
	out << "Form: " COLOR_BLUE << f.GetName() << "("
		<< (f.GetIsSigned() ? "signed" : "not signed")
		<< ")," COLOR_END " grade for sign is " COLOR_BLUE << f.GetGradeForSign()
		<< COLOR_END ", "
		<< "grade for execute is " COLOR_BLUE << f.GetGradeForExecute() << COLOR_END;
	return out;
}

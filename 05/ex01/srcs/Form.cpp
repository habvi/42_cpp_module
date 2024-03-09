#include "Form.hpp"
#include "Bureaucrat.hpp"
#include "GradeException.hpp"
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
	if (grade_for_sign < kHighestGrade || grade_for_execute < kHighestGrade) {
		throw GradeTooHighException();
	} else if (grade_for_sign > kLowestGrade || grade_for_execute > kLowestGrade) {
		throw GradeTooLowException();
	}
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

const char *Form::GradeTooHighException() const {
	throw GradeException("Error: Grade is too high");
}

const char *Form::GradeTooLowException() const {
	throw GradeException("Error: Grade is too low");
}

bool Form::beSigned(const Bureaucrat &b) {
	if (b.getGrade() > kLowestGrade) {
		throw GradeTooLowException();
	if (b.getGrade() <= grade_for_sign_) {
		is_signed_ = true;
		return true;
	}
	return false;
}

std::ostream &operator<<(std::ostream &out, const Form &f) {
	out << COLOR_PINK << "Form " << f.GetName() << "("
		<< (f.GetIsSigned() ? "signed" : "not signed") << "), grade for sign is "
		<< f.GetGradeForSign() << ", "
		<< "grade for execute is " << f.GetGradeForExecute() << COLOR_END;
	return out;
}

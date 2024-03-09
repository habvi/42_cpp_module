#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "GradeException.hpp"
#include "color.hpp"

AForm::AForm() : grade_for_sign_(kLowestGrade), grade_for_execute_(kLowestGrade) {}

AForm::AForm(
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

AForm::AForm(const AForm &f)
	: name_(f.GetName()),
	  is_signed_(f.GetIsSigned()),
	  grade_for_sign_(f.GetGradeForSign()),
	  grade_for_execute_(f.GetGradeForExecute()) {}

AForm::~AForm() {}

const AForm &AForm::operator=(const AForm &f) {
	if (this != &f) {
		is_signed_ = f.GetIsSigned();
	}
	return *this;
}

const std::string &AForm::GetName() const {
	return name_;
}

bool AForm::GetIsSigned() const {
	return is_signed_;
}

unsigned int AForm::GetGradeForSign() const {
	return grade_for_sign_;
}

unsigned int AForm::GetGradeForExecute() const {
	return grade_for_execute_;
}

const char *AForm::GradeTooHighException() const {
	throw GradeException("Error: Grade is too high");
}

const char *AForm::GradeTooLowException() const {
	throw GradeException("Error: Grade is too low");
}

bool AForm::beSigned(const Bureaucrat &b) {
	if (b.getGrade() > kLowestGrade) {
		throw GradeTooLowException();
	}
	if (b.getGrade() <= grade_for_sign_) {
		is_signed_ = true;
		return true;
	}
	return false;
}

std::ostream &operator<<(std::ostream &out, const AForm &f) {
	out << "AForm: " COLOR_BLUE << f.GetName() << "("
		<< (f.GetIsSigned() ? "signed" : "not signed")
		<< ")," COLOR_END " grade for sign is " COLOR_BLUE << f.GetGradeForSign()
		<< COLOR_END ", "
		<< "grade for execute is " COLOR_BLUE << f.GetGradeForExecute() << COLOR_END;
	return out;
}

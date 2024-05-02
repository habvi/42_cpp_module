#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "color.hpp"

AForm::AForm()
	: grade_for_sign_(Bureaucrat::GetLowestGrade()),
	  grade_for_execute_(Bureaucrat::GetLowestGrade()) {}

AForm::AForm(
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

AForm::AForm(const AForm &f)
	: name_(f.GetName()),
	  is_signed_(f.GetIsSigned()),
	  grade_for_sign_(f.GetGradeForSign()),
	  grade_for_execute_(f.GetGradeForExecute()) {}

AForm::~AForm() {}

AForm &AForm::operator=(const AForm &f) {
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

void AForm::beSigned(const Bureaucrat &b) {
	if (b.getGrade() > grade_for_sign_) {
		AForm::GradeTooLowException();
	}
	is_signed_ = true;
}

void AForm::execute(Bureaucrat const &executor) const {
	if (!is_signed_) {
		throw AForm::NotSignedException();
	}
	if (executor.getGrade() > grade_for_execute_) {
		AForm::GradeTooLowException();
	}
	ExecuteEachForm(executor);
}

void AForm::ThrowGradeException(const unsigned int grade) const {
	if (grade < Bureaucrat::GetHighestGrade()) {
		AForm::GradeTooHighException();
	} else if (grade > Bureaucrat::GetLowestGrade()) {
		AForm::GradeTooLowException();
	}
}

void AForm::GradeTooHighException() const {
	throw Bureaucrat::GradeTooHighException();
}

void AForm::GradeTooLowException() const {
	throw Bureaucrat::GradeTooLowException();
}

AForm::NotSignedException::NotSignedException()
	: std::logic_error("Error: not signed") {}

std::ostream &operator<<(std::ostream &out, const AForm &f) {
	out << "AForm: " COLOR_BLUE << f.GetName() << "("
		<< (f.GetIsSigned() ? "signed" : "not signed")
		<< ")," COLOR_END " grade for sign is " COLOR_BLUE << f.GetGradeForSign()
		<< COLOR_END ", "
		<< "grade for execute is " COLOR_BLUE << f.GetGradeForExecute() << COLOR_END;
	return out;
}

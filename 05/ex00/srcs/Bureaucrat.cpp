#include "Bureaucrat.hpp"
#include "color.hpp"

Bureaucrat::Bureaucrat() : grade_(kLowestGrade) {}

Bureaucrat::Bureaucrat(const std::string &name, const unsigned int grade)
	: name_(name) {
	ThrowGradeException(grade);
	grade_ = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &b)
	: name_(b.getName()), grade_(b.getGrade()) {}

Bureaucrat::~Bureaucrat() {}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &b) {
	if (this != &b) {
		grade_ = b.getGrade();
	}
	return *this;
}

const std::string &Bureaucrat::getName() const {
	return name_;
}

unsigned int Bureaucrat::getGrade() const {
	return grade_;
}

void Bureaucrat::IncrementGrade() {
	ThrowGradeException(grade_ - 1);
	grade_--;
}

void Bureaucrat::DecrementGrade() {
	ThrowGradeException(grade_ + 1);
	grade_++;
}

void Bureaucrat::ThrowGradeException(const unsigned int grade) const {
	if (grade < kHighestGrade) {
		throw Bureaucrat::GradeTooHighException();
	} else if (grade > kLowestGrade) {
		throw Bureaucrat::GradeTooLowException();
	}
}

// exception
Bureaucrat::GradeTooHighException::GradeTooHighException()
	: std::logic_error("Error: Grade is too high") {}

// exception
Bureaucrat::GradeTooLowException::GradeTooLowException()
	: std::logic_error("Error: Grade is too low") {}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &b) {
	out << COLOR_PINK << b.getName() << ", bureaucrat grade " << b.getGrade()
		<< "." COLOR_END;
	return out;
}

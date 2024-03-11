#include "Bureaucrat.hpp"
#include "GradeException.hpp"
#include "color.hpp"

Bureaucrat::Bureaucrat() {}

Bureaucrat::Bureaucrat(const std::string &name, const unsigned int grade)
	: name_(name) {
	if (grade < kHighestGrade) {
		throw GradeTooHighException();
	} else if (grade > kLowestGrade) {
		throw GradeTooLowException();
	}
	grade_ = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &b)
	: name_(b.getName()), grade_(b.getGrade()) {}

Bureaucrat::~Bureaucrat() {}

const Bureaucrat &Bureaucrat::operator=(const Bureaucrat &b) {
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
	if (grade_ - 1 < kHighestGrade) {
		throw GradeTooHighException();
	}
	grade_--;
}

void Bureaucrat::DecrementGrade() {
	if (grade_ + 1 > kLowestGrade) {
		throw GradeTooLowException();
	}
	grade_++;
}

const char *Bureaucrat::GradeTooHighException() const {
	throw GradeException("Error: Grade is too high");
}

const char *Bureaucrat::GradeTooLowException() const {
	throw GradeException("Error: Grade is too low");
}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &b) {
	out << COLOR_PINK << b.getName() << ", bureaucrat grade " << b.getGrade()
		<< "." COLOR_END;
	return out;
}

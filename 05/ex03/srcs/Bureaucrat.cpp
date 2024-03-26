#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "color.hpp"
#include <iostream>

Bureaucrat::Bureaucrat() : grade_(kLowestGrade) {}

Bureaucrat::Bureaucrat(const std::string &name, const unsigned int grade)
	: name_(name) {
	ThrowGradeException(grade);
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

unsigned int Bureaucrat::GetHighestGrade() {
	return kHighestGrade;
}

unsigned int Bureaucrat::GetLowestGrade() {
	return kLowestGrade;
}

void Bureaucrat::IncrementGrade() {
	ThrowGradeException(grade_ - 1);
	grade_--;
}

void Bureaucrat::DecrementGrade() {
	ThrowGradeException(grade_ + 1);
	grade_++;
}

void Bureaucrat::signForm(AForm &form) {
	try {
		form.beSigned(*this);
		std::cout << COLOR_PINK << getName() << COLOR_END " signed " COLOR_PINK
				  << form.GetName() << COLOR_END << std::endl;
	} catch (const std::exception &e) {
		std::cout << COLOR_PINK << getName()
				  << COLOR_END " couldn't sign " COLOR_PINK << form.GetName()
				  << COLOR_END << " because " COLOR_PINK << e.what() << std::endl;
		throw;
	}
}

void Bureaucrat::executeForm(const AForm &form) const {
	try {
		form.execute(*this);
		std::cout << COLOR_PINK << getName() << " execute " << form.GetName()
				  << COLOR_END << std::endl;
	} catch (const std::exception &e) {
		std::cerr << COLOR_PINK << getName() << " failed to execute => " COLOR_RED
				  << e.what() << COLOR_END << std::endl;
	}
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

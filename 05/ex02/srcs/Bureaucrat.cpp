#include "Bureaucrat.hpp"
// #include "Form.hpp"
#include "GradeException.hpp"
#include "color.hpp"
#include <iostream>

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

// void Bureaucrat::signForm(Form &form) {
// 	try {
// 		bool is_successful_sign = form.beSigned(*this);
// 		if (is_successful_sign) {
// 			std::cout << COLOR_PINK << getName() << COLOR_END " signed " COLOR_PINK
// 					  << form.GetName() << COLOR_END << std::endl;
// 		} else {
// 			std::cout << COLOR_PINK << getName()
// 					  << COLOR_END " couldn't sign " COLOR_PINK << form.GetName()
// 					  << COLOR_END << " because lower than the required Form grade."
// 					  << std::endl;
// 		}
// 	} catch (const std::exception &e) {
// 		std::cout << COLOR_PINK << getName()
// 				  << COLOR_END " couldn't sign " COLOR_PINK << form.GetName()
// 				  << COLOR_END << " because the Grade is too low" << std::endl;
// 		throw;
// 	}
// }

std::ostream &operator<<(std::ostream &out, const Bureaucrat &b) {
	out << COLOR_PINK << b.getName() << ", bureaucrat grade " << b.getGrade()
		<< "." COLOR_END;
	return out;
}

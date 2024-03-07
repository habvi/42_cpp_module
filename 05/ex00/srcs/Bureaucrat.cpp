#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() {}

Bureaucrat::Bureaucrat(const std::string &name, const unsigned int grade)
	: name_(name) {
	// todo: error throw
	grade_ = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &b)
	: name_(b.getName()), grade_(b.getGrade()) {}

Bureaucrat::~Bureaucrat() {}

const Bureaucrat &Bureaucrat::operator=(const Bureaucrat &b) {
	if (this != &b) {
		// setName(b.getName());
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

// void Bureaucrat::setName(const std::string &name) {
// 	name_ = name;
// }

void Bureaucrat::IncrementGrade() {
	if (grade_ - 1 < kHighestGrade) {
		throw;
	}
	grade_--;
}

void Bureaucrat::DecrementGrade() {
	if (grade_ + 1 > kLowestGrade) {
		throw;
	}
	grade_++;
}

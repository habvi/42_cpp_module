#include "GradeException.hpp"

GradeException::GradeException(const char *message) : message_(message) {}

GradeException::~GradeException() throw() {}

const char *GradeException::what() const throw() {
	return message_;
}

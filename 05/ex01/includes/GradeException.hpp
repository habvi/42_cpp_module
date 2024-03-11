#ifndef EX01_GRADE_EXCEPTION_HPP
#define EX01_GRADE_EXCEPTION_HPP

#include <string>

// Following the instructions,
// exception classes don’t have to be designed in Orthodox Canonical Form.
class GradeException : public std::exception {
  public:
	explicit GradeException(const char *message);
	~GradeException() throw();

  public:
	const char *what() const throw();

  private:
	const char *message_;
};

#endif /* EX01_GRADE_EXCEPTION_HPP */

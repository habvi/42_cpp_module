#ifndef EX00_SCALAR_CONVERTER_HPP
#define EX00_SCALAR_CONVERTER_HPP

#include <string>

class ScalarConverter {
  public:
	static void convert(const std::string &str);

  private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter &c);
	const ScalarConverter &operator=(const ScalarConverter &c);
	~ScalarConverter();

  private:
	static std::string src_;
};

#endif /* EX00_SCALAR_CONVERTER_HPP */

#ifndef EX00_SCALAR_CONVERTER_HPP
#define EX00_SCALAR_CONVERTER_HPP

#include <string>

class ScalarConverter {
  public:
	typedef enum e_type {
		kTypeInvalid = 0,
		kTypeChar,
		kTypeInt,
		kTypeFloat,
		kTypeDouble
	} Type;
	static void convert(const std::string &str);

  private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter &c);
	const ScalarConverter &operator=(const ScalarConverter &c);
	~ScalarConverter();

  private:
	static std::string src_;
	static Type        type_;
};

#endif /* EX00_SCALAR_CONVERTER_HPP */

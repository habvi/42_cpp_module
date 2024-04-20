#ifndef EX00_SCALAR_CONVERTER_HPP
#define EX00_SCALAR_CONVERTER_HPP

#include <limits>
#include <sstream> // ostringstream
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
	static void SetType();

	/* judge type */
	static bool IsTypeChar();
	static bool IsTypeInteger();
	static bool IsIntegerRangeForFloat(const float &num);
	static bool IsTypeFloat();
	static bool IsTypeDouble(const std::string &str);
	/* _judge.hpp */
	template <typename T>
	static bool IsValidRange(const double &num);
	template <typename T>
	static bool IsCharRange(const T &scalar);
	template <typename T>
	static bool IsIntegerRange(const T &scalar);
	template <typename T>
	static bool IsFloatRange(const T &num);

	/* display */
	template <typename T>
	static void DisplayAll(const T scalar);

	/* set convert to each type */
	static void SetImpossible();
	template <typename T>
	static void SetFixed(const T &t);
	template <typename T>
	static void SetToChar(const T &num);
	template <typename T>
	static void SetToInteger(const T &num);
	template <typename T>
	static void SetToFloat(const T &num);
	template <typename T>
	static void SetToDouble(const T &num);

  private:
	/* constant */
	static const std::string kMessageImpossible;
	static const std::string kMessageNonDisplayable;
	static const int         kPrecision = 1;
	/* variables */
	static std::string        src_;
	static Type               type_;
	static std::ostringstream oss_;
};

#include "ScalarConverter_judge.tpp"

#endif /* EX00_SCALAR_CONVERTER_HPP */

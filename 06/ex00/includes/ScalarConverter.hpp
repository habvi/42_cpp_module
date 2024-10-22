#ifndef EX00_SCALAR_CONVERTER_HPP
#define EX00_SCALAR_CONVERTER_HPP

#include "utils.hpp"
#include <limits>
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
	static void convert(const std::string &src);

  private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter &c);
	ScalarConverter &operator=(const ScalarConverter &c);
	~ScalarConverter();

  private:
	static Type SetType(const std::string &src);

	/* judge type */
	static bool IsTypeChar(const std::string &src);
	static bool IsTypeInteger(const std::string &src);
	static bool IsIntegerRangeForFloat(float num);
	static bool IsTypeFloat(const std::string &src);
	static bool IsTypeDouble(const std::string &src);
	template <typename T>
	static bool IsValidRange(double num);
	template <typename T>
	static bool IsCharRange(Type type, const T &scalar);
	template <typename T>
	static bool IsIntegerRange(Type type, const T &scalar);
	template <typename T>
	static bool IsFloatRange(const T &num);

	/* display */
	template <typename T>
	static void DisplayAll(Type type, const T scalar);

	/* set convert to each type */
	static void SetImpossible();
	template <typename T>
	static void SetFixed(const T &t);
	template <typename T>
	static void SetToChar(Type type, const T &num);
	template <typename T>
	static void SetToInteger(Type type, const T &num);
	template <typename T>
	static void SetToFloat(Type type, const T &num);
	template <typename T>
	static void SetToDouble(Type type, const T &num);

  private:
	/* constant */
	static const std::string kMessageImpossible;
	static const std::string kMessageNonDisplayable;
	static const int         kPrecision = 1;
};

#endif /* EX00_SCALAR_CONVERTER_HPP */

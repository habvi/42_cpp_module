#ifndef EX00_SCALAR_CONVERTER_HPP
#define EX00_SCALAR_CONVERTER_HPP

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
	static bool IsTypeFloat();
	static bool IsTypeDouble();
	static bool IsTypeDouble(const std::string &str);

	static bool   IsIntegerRange(const double &num);
	static double ConvertStrToDouble(const std::string &str, bool &err);

	/* convert */
	static char   ConvertToChar();
	static int    ConvertToInteger();
	static float  ConvertToFloat();
	static double ConvertToDouble();

	/* display */
	template <typename T>
	static void DisplayConvertAll(const T scalar);
	template <typename T>
	static void
	Display(const std::string &title, const Type convert_to, const T scalar);

	/* set convert to each type*/
	static void SetImpossible();
	template <typename T>
	static void SetConvertEachType(const Type convert_to, const T &scalar);
	template <typename T>
	static void SetConvertToChar(const T &scalar);
	template <typename T>
	static void SetConvertToInteger(const T &scalar);
	template <typename T>
	static void SetConvertToFloat(const T &scalar);
	template <typename T>
	static void SetConvertToDouble(const T &scalar);

  private:
	/* constant */
	static const std::string kMessageImpossible;
	/* variables */
	static std::string        src_;
	static Type               type_;
	static std::ostringstream oss_;
};

#endif /* EX00_SCALAR_CONVERTER_HPP */

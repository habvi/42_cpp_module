#ifndef EX01_RPN_HPP
#define EX01_RPN_HPP

#include <string>

class RPN {
  public:
	static int Calcurate(const std::string &rpn_str);

  private:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();
	static bool IsOperations(const char c);
	static bool IsValidStr(const std::string &str);

  private:
	static const char       *kOperations;
	static const std::string kErrMsgInvalidArgument;
};

#endif /* EX01_RPN_HPP */

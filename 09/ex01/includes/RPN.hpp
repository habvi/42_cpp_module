#ifndef EX01_RPN_HPP
#define EX01_RPN_HPP

#include <string>

class RPN {
  public:
	static int Calcurate(const std::string &str);

  private:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();
};

#endif /* EX01_RPN_HPP */

#ifndef HARL_H
#define HARL_H

#include <string>

// complain
#define DEBUG   "debug"
#define INFO    "info"
#define WARNING "warning"
#define ERROR   "error"

// error
#define ERR_INVALID_LEVEL "invalid level"

// color
#define COLOR_RED   "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_END   "\033[0m"

class Harl {
  public:
	Harl();
	~Harl();

  public:
	void complain(std::string level);

  private:
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);
};

#endif /* HARL_H */

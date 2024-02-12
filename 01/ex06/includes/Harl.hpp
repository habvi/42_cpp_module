#ifndef HARL_H
#define HARL_H

#include <string>

// complain
static const std::string kDebug_   = "DEBUG";
static const std::string kInfo_    = "INFO";
static const std::string kWarning_ = "WARNING";
static const std::string kError_   = "ERROR";

// color
#define COLOR_RED "\033[31m"
#define COLOR_END "\033[0m"

class Harl {
  public:
	Harl();
	~Harl();

  public:
	void Filter(std::string level);

  private:
	typedef std::pair<std::string, void (Harl::*)()> Pair;

	void         SetComplains(Pair *complains);
	unsigned int SetLevel(const Pair *complains, const std::string &level);

  private:
	// Following the instructions, not camelcase and const qualifier isn't used.
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);

	// each level
	typedef enum {
		kLevelDebug = 0,
		kLevelInfo,
		kLevelWarning,
		kLevelError
	} Level;

	// set total number of Level
	static const unsigned int kTotalLevel_ = 4;
};

#endif /* HARL_H */

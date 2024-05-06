#ifndef EX00_BITCOIN_EXCHANGE_HPP
#define EX00_BITCOIN_EXCHANGE_HPP

#include <map>
#include <stdexcept> // logic_error
#include <string>

class BitcoinExchange {
  public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();
	class NotPositiveNumberException : public std::logic_error {
	  public:
		NotPositiveNumberException();
	};
	class TooLargeNumberException : public std::logic_error {
	  public:
		TooLargeNumberException();
	};

  public:
	void   AddRate(const std::string &date, const double rate);
	double Exchange(const std::string &date, const double amount) const;

  private:
	std::map<std::string, double> btc_rates_;
};

#endif /* EX00_BITCOIN_EXCHANGE_HPP */

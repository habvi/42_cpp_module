#ifndef EX00_BITCOIN_EXCHANGE_HPP
#define EX00_BITCOIN_EXCHANGE_HPP

#include <map>
#include <stdexcept> // logic_error,overflow_error
#include <string>

class BitcoinExchange {
  public:
	typedef std::map<std::string, double> BitcoinRates;

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
	class DuplicateDateException : public std::logic_error {
	  public:
		DuplicateDateException();
	};
	class PastDateNotFoundException : public std::logic_error {
	  public:
		PastDateNotFoundException();
	};
	class InvalidDateException : public std::logic_error {
	  public:
		InvalidDateException();
	};
	class ExchangeRateOverflowException : public std::overflow_error {
	  public:
		ExchangeRateOverflowException();
	};

  public:
	void   AddRate(const std::string &date, const double rate);
	double Exchange(const std::string &date, const double value);

  private:
	static const double kMaxBtcValue;
	BitcoinRates        btc_rates_;
};

#endif /* EX00_BITCOIN_EXCHANGE_HPP */

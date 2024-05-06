#ifndef EX00_BITCOIN_EXCHANGE_HPP
#define EX00_BITCOIN_EXCHANGE_HPP

class BitcoinExchange {
  public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();
};

#endif /* EX00_BITCOIN_EXCHANGE_HPP */

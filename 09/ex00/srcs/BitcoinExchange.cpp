#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

// todo
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
	(void)other;
}

// todo
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other) {
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::AddRate(const std::string &date, const double rate) {
	(void)date;
	(void)rate;
}

double
BitcoinExchange::Exchange(const std::string &date, const double amount) const {
	(void)date;
	(void)amount;
	return 1;
}

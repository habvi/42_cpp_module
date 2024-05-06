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

BitcoinExchange::NotPositiveNumberException::NotPositiveNumberException()
	: std::logic_error("not a positive number.") {}

BitcoinExchange::TooLargeNumberException::TooLargeNumberException()
	: std::logic_error("too large a number.") {}

BitcoinExchange::DuplicateDateException::DuplicateDateException()
	: std::logic_error("duplicate date.") {}

void BitcoinExchange::AddRate(const std::string &date, const double rate) {
	if (btc_rates_.count(date)) {
		throw DuplicateDateException();
	}
	btc_rates_[date] = rate;
}

double
BitcoinExchange::Exchange(const std::string &date, const double amount) const {
	(void)date;
	(void)amount;
	return 1;
}

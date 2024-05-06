#include "BitcoinExchange.hpp"

const double BitcoinExchange::kMaxBtcValue = 1000;

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

BitcoinExchange::PastDateNotFoundException::PastDateNotFoundException()
	: std::logic_error("not found past date.") {}

void BitcoinExchange::AddRate(const std::string &date, const double rate) {
	if (btc_rates_.count(date)) {
		throw DuplicateDateException();
	}
	btc_rates_[date] = rate;
}

double BitcoinExchange::Exchange(const std::string &date, const double value) {
	if (value < 0) {
		throw NotPositiveNumberException();
	} else if (value > kMaxBtcValue) {
		throw TooLargeNumberException();
	}
	// todo: PastDateNotFoundException()
	// todo: check overflow
	return btc_rates_[date] * value;
}

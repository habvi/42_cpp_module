#include "BitcoinExchange.hpp"
#include <iostream> // todo
#include <limits>
#include <sstream>

const double BitcoinExchange::kMaxBtcValue = 1000;

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
	: btc_rates_(other.btc_rates_) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other) {
		btc_rates_ = other.btc_rates_;
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

BitcoinExchange::InvalidDateException::InvalidDateException()
	: std::logic_error("invalid date.") {}

BitcoinExchange::ExchangeRateOverflowException::ExchangeRateOverflowException()
	: std::logic_error("overflow exchange rate.") {}

namespace {
	int ConvertToInt(const std::string &str, int &num) {
		std::stringstream ss(str);
		ss >> num;
		return ss.eof() && !ss.fail();
	}

	bool IsValidYear(const int year) {
		return year >= 0 && year <= 9999;
	}

	bool IsValidMonth(const int month) {
		return month >= 0 && month <= 12;
	}

	bool IsValidDay(const int month, const int day) {
		if (day < 0) {
			return false;
		}
		static const int short_month[5] = {2, 4, 6, 9, 11};
		for (unsigned int i = 0; i < 5; i++) {
			if (month == short_month[i]) {
				return day <= 30;
			}
		}
		return day <= 31;
	}

	bool IsValidLeapYearDate(const int year, const int day) {
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			return day <= 29;
		} else {
			return day <= 28;
		}
	}

	bool IsValidDate(
		const std::string &yaer_str,
		const std::string &month_str,
		const std::string &day_str
	) {
		int year;
		int month;
		int day;
		if (!ConvertToInt(yaer_str, year) || !ConvertToInt(month_str, month) ||
			!ConvertToInt(day_str, day)) {
			return false;
		}
		if (!IsValidYear(year) || !IsValidMonth(month) || !IsValidDay(month, day)) {
			return false;
		}
		if (month == 2) {
			return IsValidLeapYearDate(year, day);
		}
		return true;
	}

	// Year-Month-Day / XXXX-XX-XX
	bool IsValidDateFormat(const std::string &date) {
		if (date.size() != 10) {
			return false;
		}
		if (date[4] != '-' || date[7] != '-') {
			return false;
		}
		std::string year  = date.substr(0, 4);
		std::string month = date.substr(5, 2);
		std::string day   = date.substr(8);
		return IsValidDate(year, month, day);
	}

	// value: 0 ~ 1000
	bool IsOverflow(const double rate, const double value) {
		if (value == 0) {
			return false;
		}
		if (rate < 0) {
			return rate < -std::numeric_limits<double>::max() / value;
		} else {
			return rate > std::numeric_limits<double>::max() / value;
		}
	}
} // namespace

void BitcoinExchange::AddRate(const std::string &date, const double rate) {
	if (!IsValidDateFormat(date)) {
		throw InvalidDateException();
	}
	if (btc_rates_.count(date)) {
		throw DuplicateDateException();
	}
	btc_rates_[date] = rate;
}

double BitcoinExchange::Exchange(const std::string &date, const double value) {
	if (!IsValidDateFormat(date)) {
		throw InvalidDateException();
	}
	if (value < 0) {
		throw NotPositiveNumberException();
	} else if (value > kMaxBtcValue) {
		throw TooLargeNumberException();
	}

	BitcoinRates::const_iterator itr = btc_rates_.lower_bound(date);
	if (itr->first == date) {
		const double rate = itr->second;
		if (IsOverflow(rate, value)) {
			throw ExchangeRateOverflowException();
		}
		return rate * value;
	}
	if (itr == btc_rates_.begin()) {
		throw PastDateNotFoundException();
	}
	--itr;
	const double rate = itr->second;
	if (IsOverflow(rate, value)) {
		throw ExchangeRateOverflowException();
	}
	return rate * value;
}

#include "BitcoinExchange.hpp"
#include <sstream>

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

BitcoinExchange::InvalidDateException::InvalidDateException()
	: std::logic_error("invalid date.") {}

namespace {
	int ConvertToInt(const std::string &str, int &num) {
		std::stringstream ss(str);
		ss >> num;
		return !ss.fail();
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
	std::map<std::string, double>::const_iterator itr = btc_rates_.lower_bound(date);
	if (itr->first == date) {
		return itr->second * value;
	}
	if (itr == btc_rates_.begin()) {
		throw PastDateNotFoundException();
	}
	--itr;
	const double pre_date_rate = itr->second;
	// todo: check overflow
	return pre_date_rate * value;
}

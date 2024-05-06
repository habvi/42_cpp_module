#include "BitcoinExchange.hpp"
#include "color.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

namespace {
	void PrintError(const std::string &message) {
		std::cerr << COLOR_RED "Error: " << message << COLOR_END << std::endl;
	}

	void PrintErrorOpenFileFail() {
		PrintError("could not open file.");
		std::cerr << "- Usage: ./btc *.txt" << std::endl;
	}

	// OK: *.txt
	bool IsValidInfileType(const char *path) {
		std::ifstream infile(path);
		if (!infile) {
			return false;
		}
		static const std::string     kExtension = ".txt";
		const std::string            path_str(path);
		const std::string::size_type pos = path_str.rfind(kExtension);
		return pos != std::string::npos &&
			   pos + kExtension.size() == path_str.size();
	}

	// -------------------------------------------------------------------------
	// <date>,<rate>
	bool ParseData(
		const size_t       line_num,
		const std::string &line,
		std::string       &date,
		double            &rate
	) {
		if (line_num == 1) {
			return line == "date,exchange_rate";
		}

		static const char      kDelim          = ',';
		std::string::size_type delim_pos       = line.find(kDelim);
		std::string::size_type delim_pos_right = line.rfind(kDelim);
		if (delim_pos == std::string::npos || delim_pos + 1 == line.size() ||
			delim_pos != delim_pos_right) {
			return false;
		}

		date = line.substr(0, delim_pos);
		// todo: check date format
		std::string       rate_str = line.substr(delim_pos + 1);
		std::stringstream ss(rate_str);
		ss >> rate;
		return !ss.fail();
	}

	bool AddBitcoinRates(BitcoinExchange &btc) {
		static size_t      line_num             = 0;
		static const char *kBitcoinRateFilepath = "data_tmp.csv"; // todo

		std::ifstream infile(kBitcoinRateFilepath);
		if (!infile) {
			PrintError("could not open " + std::string(kBitcoinRateFilepath));
			return false;
		}
		std::string line;
		while (std::getline(infile, line)) {
			line_num++;
			std::string date;
			double      rate = 0;
			if (infile.fail() || !ParseData(line_num, line, date, rate)) {
				PrintError("bad data => " + line);
				return false;
			}
			if (line_num == 1) {
				continue;
			}
			try {
				btc.AddRate(date, rate);
			} catch (const std::logic_error &e) {
				PrintError(e.what());
				return false;
			}
		}
		return true;
	}

	// -------------------------------------------------------------------------
	// <date> | <value>
	bool ParseInput(
		const size_t       line_num,
		const std::string &line,
		std::string       &date,
		double            &value
	) {
		if (line_num == 1) {
			return line == "date | value";
		}

		static const char      kDelim          = '|';
		std::string::size_type delim_pos       = line.find(kDelim);
		std::string::size_type delim_pos_right = line.rfind(kDelim);
		if (delim_pos == std::string::npos || delim_pos + 1 == line.size() ||
			delim_pos != delim_pos_right) {
			return false;
		}

		date = line.substr(0, delim_pos);
		// todo: check date format
		std::string       rate_str = line.substr(delim_pos + 1);
		std::stringstream ss(rate_str);
		ss >> value;
		return !ss.fail();
	}

	void FmtPrintResult(
		const std::string &date, const double value, const double exchange_result
	) {
		std::cout << date << " => " << value << " = " << exchange_result
				  << std::endl;
	}

	void PrintExchangeResult(BitcoinExchange &btc, const char *infile_path) {
		static size_t line_num = 0;
		std::ifstream infile(infile_path);
		std::string   line;
		while (std::getline(infile, line)) {
			line_num++;
			std::string date;
			double      value = 0;
			if (infile.fail() || !ParseInput(line_num, line, date, value)) {
				PrintError("bad input => " + line);
				continue;
			}
			if (line_num == 1) {
				continue;
			}
			try {
				const double exchange_result = btc.Exchange(date, value);
				FmtPrintResult(date, value, exchange_result);
			} catch (const std::logic_error &e) {
				PrintError(e.what());
			}
		}
	}
} // namespace

int main(int argc, char **argv) {
	if (argc != 2 || !IsValidInfileType(argv[1])) {
		PrintErrorOpenFileFail();
		return EXIT_FAILURE;
	}

	BitcoinExchange btc;
	if (!AddBitcoinRates(btc)) {
		return EXIT_FAILURE;
	}
	PrintExchangeResult(btc, argv[1]);
	return EXIT_SUCCESS;
}

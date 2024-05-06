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
	// <date><delim><num>
	bool ParseBitcoinData(
		const std::string &line,
		const std::string &delim,
		std::string       &date,
		double            &num
	) {
		std::string::size_type delim_pos       = line.find(delim);
		std::string::size_type delim_pos_right = line.rfind(delim);
		if (delim_pos == std::string::npos ||
			delim_pos + delim.size() == line.size() ||
			delim_pos != delim_pos_right) {
			return false;
		}

		date = line.substr(0, delim_pos);
		// todo: check date format?
		std::string       num_str = line.substr(delim_pos + delim.size());
		std::stringstream ss(num_str);
		ss >> num;
		return !ss.fail();
	}

	// -------------------------------------------------------------------------
	// <date>,<rate>
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
			if (infile.fail()) {
				PrintError("bad data => " + line);
				return false;
			}
			line_num++;
			if (line_num == 1) {
				if (line != "date,exchange_rate") {
					return false;
				}
				continue;
			}
			std::string date;
			double      rate;
			if (!ParseBitcoinData(line, ",", date, rate)) {
				PrintError("bad data => " + line);
				return false;
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
	void FmtPrintResult(
		const std::string &date, const double value, const double exchange_result
	) {
		std::cout << date << " => " << value << " = " << exchange_result
				  << std::endl;
	}

	// <date> | <value>
	void PrintExchangeResult(BitcoinExchange &btc, const char *infile_path) {
		static size_t line_num = 0;
		std::ifstream infile(infile_path);
		std::string   line;
		while (std::getline(infile, line)) {
			if (infile.fail()) {
				PrintError("bad input => " + line);
				continue;
			}
			line_num++;
			if (line_num == 1) {
				// todo
				if (line != "date | value") {
					PrintError("bad input => " + line);
				}
				continue;
			}
			std::string date;
			double      value;
			if (!ParseBitcoinData(line, " | ", date, value)) {
				PrintError("bad input => " + line);
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

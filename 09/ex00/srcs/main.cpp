#include "BitcoinExchange.hpp"
#include "color.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

namespace {
	static const char       *kBitcoinRateFilepath = "data_tmp.csv"; // todo
	static const std::string kDataFileHead        = "date,exchange_rate";
	static const std::string kDataFileDelimiter   = ",";
	static const std::string kErrBadData          = "bad data => ";
	static const std::string kInputFileHead       = "date | value";
	static const std::string kInputFileDelimiter  = " | ";
	static const std::string kErrBadInput         = "bad input => ";

	// -------------------------------------------------------------------------
	void PrintError(const std::string &message) {
		std::cerr << COLOR_RED "Error: " << message << COLOR_END << std::endl;
	}

	void PrintErrorOpenFileFail() {
		PrintError("could not open file.");
		std::cerr << "- Usage: ./btc *.txt" << std::endl;
	}

	bool IsValidFileType(const char *path, const std::string &extension) {
		const std::string            path_str(path);
		const std::string::size_type pos = path_str.rfind(extension);
		if (pos == std::string::npos || pos + extension.size() != path_str.size()) {
			PrintErrorOpenFileFail();
			return false;
		}
		return true;
	}

	bool OpenFile(const char *filepath, std::ifstream &file) {
		file.open(filepath);
		if (!file) {
			PrintError("could not open " + std::string(filepath));
			return false;
		}
		return true;
	}

	bool IsValidFileHeadLine(std::ifstream &file, const std::string &head_str) {
		std::string head_line;
		std::getline(file, head_line);
		if (file.fail() || head_line != head_str) {
			PrintError("invalid file.");
			return false;
		}
		return true;
	}

	bool OpenValidDataFile(const char *btc_rate_filepath, std::ifstream &file) {
		return IsValidFileType(btc_rate_filepath, ".csv") &&
			   OpenFile(btc_rate_filepath, file) &&
			   IsValidFileHeadLine(file, kDataFileHead);
	}

	bool OpenValidInputFile(const char *input_filepath, std::ifstream &file) {
		return IsValidFileType(input_filepath, ".txt") &&
			   OpenFile(input_filepath, file) &&
			   IsValidFileHeadLine(file, kInputFileHead);
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

		date                      = line.substr(0, delim_pos);
		const std::string num_str = line.substr(delim_pos + delim.size());
		std::stringstream ss(num_str);
		ss >> num;
		return ss.eof() && !ss.fail();
	}

	// -------------------------------------------------------------------------
	// <date>,<rate>
	bool AddBitcoinRates(BitcoinExchange &btc, std::ifstream &btc_rate_file) {
		std::string line;
		while (std::getline(btc_rate_file, line)) {
			if (btc_rate_file.fail()) {
				PrintError(kErrBadData + line);
				return false;
			}
			std::string date;
			double      rate;
			if (!ParseBitcoinData(line, kDataFileDelimiter, date, rate)) {
				PrintError(kErrBadData + line);
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
	void PrintExchangeResult(BitcoinExchange &btc, std::ifstream &input_file) {
		std::string line;
		while (std::getline(input_file, line)) {
			if (input_file.fail()) {
				PrintError(kErrBadInput + line);
				continue;
			}
			std::string date;
			double      value;
			if (!ParseBitcoinData(line, kInputFileDelimiter, date, value)) {
				PrintError(kErrBadInput + line);
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
	if (argc != 2) {
		PrintErrorOpenFileFail();
		return EXIT_FAILURE;
	}

	std::ifstream data_file;
	if (!OpenValidDataFile(kBitcoinRateFilepath, data_file)) {
		return EXIT_FAILURE;
	}
	BitcoinExchange btc;
	if (!AddBitcoinRates(btc, data_file)) {
		return EXIT_FAILURE;
	}
	std::ifstream input_file;
	if (!OpenValidInputFile(argv[1], input_file)) {
		return EXIT_FAILURE;
	}
	PrintExchangeResult(btc, input_file);
	return EXIT_SUCCESS;
}

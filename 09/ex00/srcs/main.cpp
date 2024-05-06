#include "BitcoinExchange.hpp"
#include "color.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>

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
	void AddBitcoinRates(BitcoinExchange &btc) {
		static const std::string &kBitcoinRateFilepath = "data.csv";
		std::string               date;
		double                    rate = 0;
		btc.AddRate(date, rate);
	}

	// -------------------------------------------------------------------------
	bool ParseLine(const std::string &line, std::string &date, double &value) {
		(void)line;
		(void)date;
		(void)value;
		return true;
	}

	void FmtPrintResult(
		const std::string &date, const double value, const double exchange_result
	) {
		std::cout << date << " => " << value << " = " << exchange_result
				  << std::endl;
	}

	void PrintExchangeResult(BitcoinExchange &btc, const char *infile_path) {
		std::ifstream infile(infile_path);
		std::string   line;
		while (std::getline(infile, line) && !line.empty()) {
			std::string date;
			double      value = 0;
			if (infile.fail() || !ParseLine(line, date, value)) {
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
	AddBitcoinRates(btc);
	PrintExchangeResult(btc, argv[1]);

	return EXIT_SUCCESS;
}

#include "BitcoinExchange.hpp"
#include "color.hpp"
#include <cstdlib>
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
	void PrintExchangeResult(const BitcoinExchange &btc, const char *infile_path) {
		(void)btc;
		(void)infile_path;
		std::string  date;
		double       amount          = 0;
		const double exchange_result = btc.Exchange(date, amount);
		(void)exchange_result;
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

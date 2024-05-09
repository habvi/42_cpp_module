#include "PmergeMe.hpp"
#include "color.hpp"
#include <cctype> // isdigit
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

namespace {
	// Following the instructions,  output to STDOUT in case of an error.
	void PrintError(const std::string &message) {
		std::cout << COLOR_RED << "Error: " << message << COLOR_END << std::endl;
	}

	std::vector<std::string> ToStrVec(const char *const *argv) {
		std::vector<std::string> pmerge_strs;
		for (std::size_t i = 0; argv[i]; i++) {
			pmerge_strs.push_back(std::string(argv[i]));
		}
		return pmerge_strs;
	}

	bool MyIsDigit(const char c) {
		return std::isdigit(static_cast<unsigned char>(c));
	}

	bool ConvertStrToInt(const std::string &str, unsigned int &num) {
		std::stringstream ss(str);
		ss >> num;
		return ss.eof() && !ss.fail();
	}

	// ok: 0 ~ UINT_MAX integer
	bool ConvertToPmergeVec(
		const std::vector<std::string> &pmerge_str, PmergeMe::PmergeVec &pmerge_vec
	) {
		for (std::size_t i = 0; i < pmerge_str.size(); i++) {
			if (!pmerge_str[i].empty() && !MyIsDigit(pmerge_str[i][0])) {
				return false;
			}
			unsigned int num;
			if (!ConvertStrToInt(pmerge_str[i], num)) {
				return false;
			}
			pmerge_vec.push_back(num);
		}
		return true;
	}

	void PrintResult(
		const std::vector<std::string> pmerge_strs,
		const PmergeMe::PmergeVec     &result_nums
	) {
		std::cout << "Before: ";
		for (std::size_t i = 0; i < pmerge_strs.size(); i++) {
			std::cout << pmerge_strs[i] << " ";
		}
		std::cout << std::endl;

		std::cout << "After: ";
		for (std::size_t i = 0; i < result_nums.size(); i++) {
			std::cout << result_nums[i] << " ";
		}
		std::cout << std::endl;
	}

	bool MergeInsertSortWithVector(const char *const *argv) {
		const std::vector<std::string> pmerge_strs = ToStrVec(&argv[1]);
		PmergeMe::PmergeVec            pmerge_vec;
		if (!ConvertToPmergeVec(pmerge_strs, pmerge_vec)) {
			PrintError("invalid argument");
			return false;
		}

		const PmergeMe::PmergeVec result_nums =
			PmergeMe::MergeInsertSort(pmerge_vec);
		PrintResult(pmerge_strs, result_nums);
		return true;
	}
} // namespace

int main(int argc, char **argv) {
	if (argc == 1) {
		PrintError("invalid argument");
		return EXIT_FAILURE;
	}

	if (!MergeInsertSortWithVector((const char *const *)argv)) {
		return EXIT_FAILURE;
	}
	// MergeInsertSortWithList();

	return EXIT_SUCCESS;
}

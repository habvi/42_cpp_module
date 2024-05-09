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
	bool ConvertToIntVec(
		const std::vector<std::string> &vec_strs, std::vector<unsigned int> &vec_nums
	) {
		for (std::size_t i = 0; i < vec_strs.size(); i++) {
			if (!vec_strs[i].empty() && !MyIsDigit(vec_strs[i][0])) {
				return false;
			}
			unsigned int num;
			if (!ConvertStrToInt(vec_strs[i], num)) {
				return false;
			}
			vec_nums.push_back(num);
		}
		return true;
	}

	bool IsDuplicateNums(const std::vector<unsigned int> &vec_nums) {
		// todo
		return false;
	}

	bool ConvertValidIntVec(
		const char *const *argv, std::vector<unsigned int> &vec_nums
	) {
		const std::vector<std::string> vec_strs = ToStrVec(&argv[1]);
		if (!ConvertToIntVec(vec_strs, vec_nums)) {
			PrintError("invalid argument");
			return false;
		}
		if (IsDuplicateNums(vec_nums)) {
			PrintError("invalid argument");
			return false;
		}
		return true;
	}

	void PrintResult(
		const PmergeMe::PmergeVec &pmerge_vec, const PmergeMe::PmergeVec &result_nums
	) {
		std::cout << "Before: ";
		for (std::size_t i = 0; i < pmerge_vec.size(); i++) {
			std::cout << pmerge_vec[i] << " ";
		}
		std::cout << std::endl;

		std::cout << "After: ";
		for (std::size_t i = 0; i < result_nums.size(); i++) {
			std::cout << result_nums[i] << " ";
		}
		std::cout << std::endl;
	}

	bool MergeInsertSortWithVector(const PmergeMe::PmergeVec &pmerge_vec) {
		const PmergeMe::PmergeVec result_nums =
			PmergeMe::MergeInsertSort(pmerge_vec);
		PrintResult(pmerge_vec, result_nums);
		return true;
	}
} // namespace

int main(int argc, char **argv) {
	if (argc == 1) {
		PrintError("invalid argument");
		return EXIT_FAILURE;
	}

	std::vector<unsigned int> vec_nums;
	if (!ConvertValidIntVec((const char *const *)argv, vec_nums)) {
		return EXIT_FAILURE;
	}

	// todo: time start
	if (!MergeInsertSortWithVector(vec_nums)) {
		return EXIT_FAILURE;
	}
	// todo: time stop

	// convert vec_nums -> list<unsigned int> list_nums
	// todo: time start
	// if (!MergeInsertSortWithList(list_nums)) {
	// 	return EXIT_FAILURE;
	// }
	// todo: time stop
	return EXIT_SUCCESS;
}

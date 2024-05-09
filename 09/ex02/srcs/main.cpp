#include "PmergeMe.hpp"
#include "color.hpp"
#include <algorithm>
#include <cctype> // isdigit
#include <cstdlib>
#include <iostream>
#include <set>
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
		std::set<unsigned int> unique_nums;
		for (std::size_t i = 0; i < vec_nums.size(); i++) {
			const unsigned int num = vec_nums[i];
			if (unique_nums.count(num) > 0) {
				return true;
			}
			unique_nums.insert(num);
		}
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

	std::vector<unsigned int> SortedVec(std::vector<unsigned int> vec) {
		std::vector<unsigned int> tmp_vec = vec;
		std::sort(tmp_vec.begin(), tmp_vec.end());
		return tmp_vec;
	}

	void PrintNums(const std::string &s, const std::vector<unsigned int> &nums) {
		std::cout << s;
		for (std::size_t i = 0; i < nums.size(); i++) {
			std::cout << nums[i] << " ";
		}
		std::cout << std::endl;
	}

	void PrintNumsBeforeAfter(
		const std::vector<unsigned int> &vec_nums,
		const std::vector<unsigned int> &sorted_nums
	) {
		PrintNums("Before: ", vec_nums);
		PrintNums("After: ", sorted_nums);
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
	std::vector<unsigned int> sorted_nums = SortedVec(vec_nums);
	PrintNumsBeforeAfter(vec_nums, sorted_nums);

	// todo: time start
	const PmergeMe::PmergeVec result_nums = PmergeMe::MergeInsertSort(vec_nums);
	(void)result_nums;
	// todo: time stop
	// AssertEq(result_nums, sorted_nums);

	// convert vec_nums -> list<unsigned int> list_nums
	// todo: time start
	// MergeInsertSortWithList(list_nums);
	// todo: time stop
	// AssertEq(result_nums, sorted_nums);

	return EXIT_SUCCESS;
}

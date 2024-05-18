#include "Clock.hpp"
#include "PmergeMe.hpp"
#include "color.hpp"
#include <algorithm>
#include <cctype> // isdigit
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <stdexcept> // logic_error
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
		const std::vector<std::string> vec_strs = ToStrVec(argv);
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

	std::vector<unsigned int> GetSortedNums(const std::vector<unsigned int> &vec) {
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

	template <typename T>
	void
	AssertEq(const std::vector<unsigned int> &sorted_nums, const T &result_nums) {
		static const std::string kErrMsgNotSorted = "sort is not complete.";

		if (sorted_nums.size() != result_nums.size()) {
			throw std::logic_error(kErrMsgNotSorted);
		}
		typename std::vector<unsigned int>::const_iterator begin1 =
			sorted_nums.begin();
		typename T::const_iterator begin2 = result_nums.begin();
		for (; begin1 != sorted_nums.end(); ++begin1) {
			if (*begin1 != *begin2) {
				throw std::logic_error(kErrMsgNotSorted);
			}
			++begin2;
		}
	}
} // namespace

namespace {
	void PrintForTime(int elem_size, const std::string &container) {
		std::cout << std::fixed << std::setprecision(3)
				  << "Time to process a range of " << elem_size << " elements with "
				  << std ::setw(11) << std::left << container << " : ";
	}
} // namespace

namespace {
	PmergeMe::PmergeVec ConvertToPmergeVec(const char *const *argv) {
		PmergeMe::PmergeVec pmerge_vec;
		for (std::size_t i = 0; argv[i]; i++) {
			unsigned int num;
			ConvertStrToInt(std::string(argv[i]), num);
			pmerge_vec.push_back(num);
		}
		return pmerge_vec;
	}

	PmergeMe::PmergeVec
	MergeInsertSortWithVector(int elem_size, const char *const *argv) {
		PrintForTime(elem_size, "std::vector");
		Clock clock;

		const PmergeMe::PmergeVec pmerge_vec = ConvertToPmergeVec(argv);
		const PmergeMe::PmergeVec result_nums =
			PmergeMe::MergeInsertSort(pmerge_vec);
		return result_nums;
	}
} // namespace

namespace {
	PmergeMe::PmergeList ConvertToPmergeList(const char *const *argv) {
		PmergeMe::PmergeList pmerge_list;
		for (std::size_t i = 0; argv[i]; i++) {
			unsigned int num;
			ConvertStrToInt(std::string(argv[i]), num);
			pmerge_list.push_back(num);
		}
		return pmerge_list;
	}

	PmergeMe::PmergeList
	MergeInsertSortWithList(int elem_size, const char *const *argv) {
		PrintForTime(elem_size, "std::list");
		Clock clock;

		const PmergeMe::PmergeList pmerge_list = ConvertToPmergeList(argv);
		const PmergeMe::PmergeList result_nums =
			PmergeMe::MergeInsertSort(pmerge_list);
		return result_nums;
	}
} // namespace

int main(int argc, char **argv) {
	if (argc == 1) {
		PrintError("invalid argument");
		return EXIT_FAILURE;
	}

	std::vector<unsigned int> vec_nums;
	if (!ConvertValidIntVec((const char *const *)&argv[1], vec_nums)) {
		return EXIT_FAILURE;
	}
	const std::vector<unsigned int> sorted_nums = GetSortedNums(vec_nums);
	PrintNumsBeforeAfter(vec_nums, sorted_nums);

	// 1st container
	const PmergeMe::PmergeVec result_vec =
		MergeInsertSortWithVector(argc - 1, (const char *const *)&argv[1]);
	AssertEq(sorted_nums, result_vec);

	// 2nd container
	const PmergeMe::PmergeList result_list =
		MergeInsertSortWithList(argc - 1, (const char *const *)&argv[1]);
	AssertEq(sorted_nums, result_list);

	return EXIT_SUCCESS;
}

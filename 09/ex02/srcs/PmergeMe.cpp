#include "PmergeMe.hpp"
#include <algorithm> // todo: rm (sort)

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) {
	(void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
	if (this != &other) {
		(void)other;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

namespace {
	bool operator<(const PmergeMe::Num &num1, const PmergeMe::Num &num2) {
		return num1.num < num2.num;
	}

	// todo: constructor?
	PmergeMe::Num GetNum(unsigned int num, std::size_t index) {
		PmergeMe::Num num_idx;
		num_idx.num   = num;
		num_idx.index = index;
		return num_idx;
	}

	PmergeMe::NumPair
	GetNumPair(const PmergeMe::Num &large, const PmergeMe::Num &small) {
		PmergeMe::NumPair num_pair;
		num_pair.large = GetNum(large.num, large.index);
		num_pair.small = GetNum(small.num, small.index);
		return num_pair;
	}
} // namespace

// ----------------------------------------------------------------------------
// vector
// ----------------------------------------------------------------------------
namespace {
	std::vector<PmergeMe::NumPair>
	MargeLargerPair(const std::vector<PmergeMe::NumPair> &num_pairs) {
		std::vector<PmergeMe::NumPair> large_half_pairs;

		for (std::size_t i = 0; i + 1 < num_pairs.size(); i += 2) {
			const PmergeMe::Num num1 = GetNum(num_pairs[i].large.num, i);
			const PmergeMe::Num num2 = GetNum(num_pairs[i + 1].large.num, i + 1);
			PmergeMe::NumPair   num_pair;
			if (num1 < num2) {
				num_pair = GetNumPair(num2, num1);
			} else {
				num_pair = GetNumPair(num1, num2);
			}
			large_half_pairs.push_back(num_pair);
		}
		return large_half_pairs;
	}

	std::vector<PmergeMe::NumPair> ConvertToPairs(const PmergeMe::PmergeVec &nums) {
		std::vector<PmergeMe::NumPair> nums_pair;
		for (std::size_t i = 0; i < nums.size(); i++) {
			const PmergeMe::Num     num      = GetNum(nums[i], i);
			const PmergeMe::NumPair num_pair = GetNumPair(num, num);
			nums_pair.push_back(num_pair);
		}
		return nums_pair;
	}

	PmergeMe::PmergeVec ConvertToVec(const std::vector<PmergeMe::Num> &result_pairs
	) {
		PmergeMe::PmergeVec result_vec;
		for (std::size_t i = 0; i < result_pairs.size(); i++) {
			result_vec.push_back(result_pairs[i].num);
		}
		return result_vec;
	}
} // namespace

std::vector<PmergeMe::Num> PmergeMe::MergeInsertSortWithVec(
	const std::vector<PmergeMe::NumPair> &num_pairs, std::size_t nums_size
) {
	if (num_pairs.size() == 1) {
		std::vector<PmergeMe::Num> result_vec;
		result_vec.push_back(num_pairs[0].large);
		return result_vec;
	}

	// merge
	std::vector<NumPair> large_half_pairs = MargeLargerPair(num_pairs);

	// recursive sort
	std::vector<Num> sorted_nums =
		MergeInsertSortWithVec(large_half_pairs, nums_size);
	if (sorted_nums.size() == nums_size) {
		return sorted_nums;
	}

	// insert
	// sorted_nums = InsertSmallerNums(sorted_nums, large_half_pairs, num_pairs);
	return sorted_nums;
}

PmergeMe::PmergeVec PmergeMe::MergeInsertSort(const PmergeVec &nums) {
	std::vector<NumPair> nums_pair  = ConvertToPairs(nums);
	std::vector<Num> result_pairs   = MergeInsertSortWithVec(nums_pair, nums.size());
	PmergeMe::PmergeVec sorted_nums = ConvertToVec(result_pairs);
	// return ConvertToVec(result_pairs);

	PmergeVec tmp_vec = nums;
	std::sort(tmp_vec.begin(), tmp_vec.end());
	return tmp_vec;
}

// ----------------------------------------------------------------------------
// todo : list
// ----------------------------------------------------------------------------
PmergeMe::PmergeList PmergeMe::MergeInsertSort(const PmergeList &nums) {
	PmergeMe::PmergeList tmp_list(nums);
	tmp_list.sort();
	return tmp_list;
}

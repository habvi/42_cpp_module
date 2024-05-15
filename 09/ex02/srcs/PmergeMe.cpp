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
	std::vector<PmergeMe::NumPair> ConvertToPairs(const PmergeMe::PmergeVec &nums) {
		std::vector<PmergeMe::NumPair> nums_pair;
		for (std::size_t i = 0; i < nums.size(); i++) {
			const PmergeMe::Num     num      = GetNum(nums[i], i);
			const PmergeMe::NumPair num_pair = GetNumPair(num, num);
			nums_pair.push_back(num_pair);
		}
		return nums_pair;
	}
} // namespace

PmergeMe::PmergeVec PmergeMe::MergeInsertSort(const PmergeVec &nums) {
	std::vector<NumPair> nums_pair = ConvertToPairs(nums);
	(void)nums_pair;
	// std::vector<Num> result_pairs  = MergeInsertSortWithVec(nums_pair,
	// nums.size());
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

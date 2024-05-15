#include "PmergeMe.hpp"
#include <algorithm> // todo: rm (sort)
#include <cmath>     // pow
#include <limits>    // numeric_limits
#include <stdexcept> // logic_error

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

	std::vector<PmergeMe::Num> MakeInsertSmallNums(
		std::vector<PmergeMe::Num>           &sorted_nums,
		const std::vector<PmergeMe::NumPair> &pre_num_pairs,
		const std::vector<PmergeMe::NumPair> &num_pairs
	) {
		std::vector<PmergeMe::Num> insert_small_nums;

		if (sorted_nums.size() == 1) {
			insert_small_nums.push_back(pre_num_pairs[0].small);
		} else {
			for (std::size_t i = 0; i < sorted_nums.size(); i++) {
				// recover large to small in O(1) & update the index
				const std::size_t pre_index = sorted_nums[i].index;
				sorted_nums[i].index        = pre_num_pairs[pre_index].large.index;
				const PmergeMe::Num small   = pre_num_pairs[pre_index].small;
				insert_small_nums.push_back(small);
			}
		}
		if (num_pairs.size() > 1 && num_pairs.size() % 2 == 1) {
			const PmergeMe::Num large = GetNum(
				num_pairs[num_pairs.size() - 1].large.num, num_pairs.size() - 1
			);
			insert_small_nums.push_back(large);
		}
		return insert_small_nums;
	}

	// insert right to left in each group
	std::vector<PmergeMe::Num> &InsertSmallerNumsWithEachGroup(
		unsigned int                      group_size,
		unsigned int                      total_group_size,
		std::vector<PmergeMe::Num>       &sorted_nums,
		const std::vector<PmergeMe::Num> &insert_small_nums
	) {
		(void)group_size;
		(void)total_group_size;
		(void)insert_small_nums;
		return sorted_nums;
	}

	// term | i-th num | total
	//  0       0          0
	//  1       2          2
	//  2       2          4
	//  3       6          10
	//  4       10         20
	//  5       22         42
	//  6       42         84
	//  7       86         170
	//  8       170        340
	//  9       342        682
	//  10      682        1364
	//  11      1366       2730
	//  12      2730       5460
	//           :
	//  30   715827882  1431655764
	unsigned int GetJacobsthalNum(unsigned int term) {
		if (term == 0) {
			return 0;
		}
		const double num = (std::pow(2, term) - std::pow(-1, term)) / 3 * 2;
		if (num < std::numeric_limits<unsigned int>::min() ||
			num > std::numeric_limits<unsigned int>::max()) {
			throw std::logic_error("too large term");
		}
		return num;
	}

	std::vector<PmergeMe::Num> InsertSmallerNumsByGroup(
		std::vector<PmergeMe::Num>       &sorted_nums,
		const std::vector<PmergeMe::Num> &insert_small_nums
	) {
		// insert front
		sorted_nums.insert(sorted_nums.begin(), insert_small_nums.front());

		// insert front+1~
		std::size_t  insert_small_nums_size = insert_small_nums.size() - 1;
		unsigned int total_group_size       = 0;
		for (std::size_t i = 1; total_group_size < insert_small_nums_size; i++) {
			unsigned int group_size = GetJacobsthalNum(i);
			total_group_size += group_size;
			if (total_group_size > insert_small_nums_size) {
				const unsigned int over_num =
					total_group_size - insert_small_nums_size;
				group_size -= over_num;
				total_group_size -= over_num;
			}
			sorted_nums = InsertSmallerNumsWithEachGroup(
				group_size, total_group_size, sorted_nums, insert_small_nums
			);
		}
		return sorted_nums;
	}

	// binary search & insert smaller numbers
	std::vector<PmergeMe::Num> &InsertSmallerNums(
		std::vector<PmergeMe::Num>           &sorted_nums,
		const std::vector<PmergeMe::NumPair> &pre_num_pairs,
		const std::vector<PmergeMe::NumPair> &num_pairs
	) {
		const std::vector<PmergeMe::Num> insert_small_nums =
			MakeInsertSmallNums(sorted_nums, pre_num_pairs, num_pairs);

		sorted_nums = InsertSmallerNumsByGroup(sorted_nums, insert_small_nums);
		return sorted_nums;
	}

	// ------------------------------------------------------------------------
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
	sorted_nums = InsertSmallerNums(sorted_nums, large_half_pairs, num_pairs);
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

#include "PmergeMe.hpp"
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
} // namespace

// ----------------------------------------------------------------------------
// vector
// ----------------------------------------------------------------------------
namespace sort_vector {
	bool operator<(const PmergeMe::VNum &num1, const PmergeMe::VNum &num2) {
		return num1.num < num2.num;
	}

	// todo: constructor?
	PmergeMe::VNum GetNum(unsigned int num, std::size_t index) {
		PmergeMe::VNum num_idx;
		num_idx.num   = num;
		num_idx.index = index;
		return num_idx;
	}

	PmergeMe::VNumPair
	GetNumPair(const PmergeMe::VNum &large, const PmergeMe::VNum &small) {
		PmergeMe::VNumPair num_pair;
		num_pair.large = GetNum(large.num, large.index);
		num_pair.small = GetNum(small.num, small.index);
		return num_pair;
	}

	std::vector<PmergeMe::VNumPair>
	MargeLargerPair(const std::vector<PmergeMe::VNumPair> &num_pairs) {
		std::vector<PmergeMe::VNumPair> large_half_pairs;

		for (std::size_t i = 0; i + 1 < num_pairs.size(); i += 2) {
			const PmergeMe::VNum num1 = GetNum(num_pairs[i].large.num, i);
			const PmergeMe::VNum num2 = GetNum(num_pairs[i + 1].large.num, i + 1);
			PmergeMe::VNumPair   num_pair;
			if (num1 < num2) {
				num_pair = GetNumPair(num2, num1);
			} else {
				num_pair = GetNumPair(num1, num2);
			}
			large_half_pairs.push_back(num_pair);
		}
		return large_half_pairs;
	}

	std::vector<PmergeMe::VNum> MakeInsertSmallNums(
		std::vector<PmergeMe::VNum>           &sorted_nums,
		const std::vector<PmergeMe::VNumPair> &pre_num_pairs,
		const std::vector<PmergeMe::VNumPair> &num_pairs
	) {
		std::vector<PmergeMe::VNum> insert_small_nums;

		if (sorted_nums.size() == 1) {
			insert_small_nums.push_back(pre_num_pairs[0].small);
		} else {
			for (std::size_t i = 0; i < sorted_nums.size(); i++) {
				// recover large to small in O(1) & update the index
				const std::size_t pre_index = sorted_nums[i].index;
				sorted_nums[i].index        = pre_num_pairs[pre_index].large.index;
				const PmergeMe::VNum small  = pre_num_pairs[pre_index].small;
				insert_small_nums.push_back(small);
			}
		}
		if (num_pairs.size() > 1 && num_pairs.size() % 2 == 1) {
			const PmergeMe::VNum large = GetNum(
				num_pairs[num_pairs.size() - 1].large.num, num_pairs.size() - 1
			);
			insert_small_nums.push_back(large);
		}
		return insert_small_nums;
	}

	std::size_t BinarySearch(
		const std::vector<PmergeMe::VNum> &sorted_nums,
		const PmergeMe::VNum              &insert_num,
		std::size_t                        idx_left,
		std::size_t                        idx_right
	) {
		while (idx_right < idx_left) {
			std::size_t middle = (idx_left + idx_right) / 2;
			if (middle >= sorted_nums.size() || insert_num < sorted_nums[middle]) {
				idx_left = middle;
			} else {
				idx_right = middle + 1;
			}
		}
		return idx_right;
	}

	std::size_t InsertNumWithBinarySearch(
		std::vector<PmergeMe::VNum> &sorted_nums,
		const PmergeMe::VNum        &insert_num,
		std::size_t                  idx_large_group_last
	) {
		std::size_t pos =
			BinarySearch(sorted_nums, insert_num, idx_large_group_last, 0);

		sorted_nums.insert(sorted_nums.begin() + pos, insert_num);
		return pos;
	}

	// insert right to left in each group
	std::vector<PmergeMe::VNum> &InsertSmallerNumsWithEachGroup(
		unsigned int                       group_size,
		unsigned int                       total_group_size,
		std::vector<PmergeMe::VNum>       &sorted_nums,
		const std::vector<PmergeMe::VNum> &insert_small_nums
	) {
		// 1 + : already inserted front
		const unsigned int offset               = 1 + total_group_size - group_size;
		std::size_t        idx_large_group_last = offset + total_group_size;

		for (std::size_t i = 0; i < group_size; i++) {
			const PmergeMe::VNum insert_num =
				insert_small_nums[total_group_size - i];

			std::size_t pos = InsertNumWithBinarySearch(
				sorted_nums, insert_num, idx_large_group_last
			);
			if (pos == idx_large_group_last) {
				idx_large_group_last--;
			}
		}
		return sorted_nums;
	}

	void ResizeExcessGroup(
		unsigned int &group_size,
		unsigned int &total_group_size,
		std::size_t   insert_small_nums_size
	) {
		if (total_group_size > insert_small_nums_size) {
			const unsigned int over_num = total_group_size - insert_small_nums_size;
			group_size -= over_num;
			total_group_size -= over_num;
		}
	}

	std::vector<PmergeMe::VNum> InsertSmallerNumsByGroup(
		std::vector<PmergeMe::VNum>       &sorted_nums,
		const std::vector<PmergeMe::VNum> &insert_small_nums
	) {
		// insert front
		sorted_nums.insert(sorted_nums.begin(), insert_small_nums.front());

		// insert front+1~
		std::size_t  insert_small_nums_size = insert_small_nums.size() - 1;
		unsigned int total_group_size       = 0;
		for (std::size_t i = 1; total_group_size < insert_small_nums_size; i++) {
			unsigned int group_size = GetJacobsthalNum(i);
			total_group_size += group_size;
			ResizeExcessGroup(group_size, total_group_size, insert_small_nums_size);

			sorted_nums = InsertSmallerNumsWithEachGroup(
				group_size, total_group_size, sorted_nums, insert_small_nums
			);
		}
		return sorted_nums;
	}

	// binary search & insert smaller numbers
	std::vector<PmergeMe::VNum> &InsertSmallerNums(
		std::vector<PmergeMe::VNum>           &sorted_nums,
		const std::vector<PmergeMe::VNumPair> &pre_num_pairs,
		const std::vector<PmergeMe::VNumPair> &num_pairs
	) {
		const std::vector<PmergeMe::VNum> insert_small_nums =
			MakeInsertSmallNums(sorted_nums, pre_num_pairs, num_pairs);

		sorted_nums = InsertSmallerNumsByGroup(sorted_nums, insert_small_nums);
		return sorted_nums;
	}

	std::vector<PmergeMe::VNum> MergeInsertSortWithVec(
		const std::vector<PmergeMe::VNumPair> &num_pairs, std::size_t nums_size
	) {
		if (num_pairs.size() == 1) {
			std::vector<PmergeMe::VNum> result_vec;
			result_vec.push_back(num_pairs[0].large);
			return result_vec;
		}

		// merge
		std::vector<PmergeMe::VNumPair> large_half_pairs =
			MargeLargerPair(num_pairs);

		// recursive sort
		std::vector<PmergeMe::VNum> sorted_nums =
			MergeInsertSortWithVec(large_half_pairs, nums_size);
		if (sorted_nums.size() == nums_size) {
			return sorted_nums;
		}

		// insert
		sorted_nums = InsertSmallerNums(sorted_nums, large_half_pairs, num_pairs);
		return sorted_nums;
	}

	// ------------------------------------------------------------------------
	std::vector<PmergeMe::VNumPair> ConvertToPairs(const PmergeMe::PmergeVec &nums) {
		std::vector<PmergeMe::VNumPair> nums_pair;
		for (std::size_t i = 0; i < nums.size(); i++) {
			const PmergeMe::VNum     num      = GetNum(nums[i], i);
			const PmergeMe::VNumPair num_pair = GetNumPair(num, num);
			nums_pair.push_back(num_pair);
		}
		return nums_pair;
	}

	PmergeMe::PmergeVec ConvertToVec(const std::vector<PmergeMe::VNum> &result_pairs
	) {
		PmergeMe::PmergeVec result_vec;
		for (std::size_t i = 0; i < result_pairs.size(); i++) {
			result_vec.push_back(result_pairs[i].num);
		}
		return result_vec;
	}
} // namespace sort_vector

PmergeMe::PmergeVec PmergeMe::MergeInsertSort(const PmergeVec &nums) {
	std::vector<VNumPair> nums_pair = sort_vector::ConvertToPairs(nums);
	std::vector<VNum>     result_pairs =
		sort_vector::MergeInsertSortWithVec(nums_pair, nums.size());
	return sort_vector::ConvertToVec(result_pairs);
}

// ----------------------------------------------------------------------------
// list
// ----------------------------------------------------------------------------
namespace sort_list {
	bool operator<(const PmergeMe::LNum &num1, const PmergeMe::LNum &num2) {
		return num1.num < num2.num;
	}

	PmergeMe::LNum GetNum(unsigned int num, const PmergeMe::ListItr &itr) {
		PmergeMe::LNum num_itr;
		num_itr.num = num;
		num_itr.itr = itr;
		return num_itr;
	}

	PmergeMe::LNumPair
	GetNumPair(const PmergeMe::LNum &large, const PmergeMe::LNum &small) {
		PmergeMe::LNumPair num_pair;
		num_pair.large = large;
		num_pair.small = small;
		return num_pair;
	}

	// for same nums pair
	PmergeMe::LNumPair GetNumPair(const PmergeMe::LNum &num) {
		PmergeMe::LNum lnum = GetNum(num.num, num.itr);
		return GetNumPair(lnum, lnum);
	}

	std::list<PmergeMe::LNumPair>::iterator
	Next(std::list<PmergeMe::LNumPair>::iterator itr) {
		return ++itr;
	}

	std::list<PmergeMe::LNum> MakeInsertSmallNums(
		std::list<PmergeMe::LNumPair>       &sorted_nums,
		const std::list<PmergeMe::LNumPair> &pre_num_pairs,
		std::list<PmergeMe::LNumPair>       &num_pairs
	) {
		std::list<PmergeMe::LNum> insert_small_nums;

		if (sorted_nums.size() == 1) {
			insert_small_nums.push_back(pre_num_pairs.begin()->small);
		} else {
			PmergeMe::ListItr first = sorted_nums.begin();
			for (; first != sorted_nums.end(); ++first) {
				const PmergeMe::ListItr pre_itr = first->large.itr;
				insert_small_nums.push_back(pre_itr->small);
				// recover large to small in O(1) & update iterator
				first->large.itr = pre_itr->large.itr;
				first->small.itr = pre_itr->large.itr;
			}
		}
		// for non-pair num
		if (num_pairs.size() > 1 && num_pairs.size() % 2 == 1) {
			const PmergeMe::ListItr itr = --num_pairs.end();
			const PmergeMe::LNum    num = GetNum(itr->large.num, itr);
			insert_small_nums.push_back(num);
		}
		return insert_small_nums;
	}

	std::list<PmergeMe::LNumPair>
	MargeLargerPair(std::list<PmergeMe::LNumPair> &num_pairs) {
		std::list<PmergeMe::LNumPair> large_half_pairs;

		PmergeMe::ListItr first = num_pairs.begin();
		for (std::size_t i = 0; i + 1 < num_pairs.size(); i += 2) {
			PmergeMe::LNum     num1 = GetNum(first->large.num, first);
			PmergeMe::ListItr  next = Next(first);
			PmergeMe::LNum     num2 = GetNum(next->large.num, next);
			PmergeMe::LNumPair num_pair;
			if (num1 < num2) {
				num_pair = GetNumPair(num2, num1);
			} else {
				num_pair = GetNumPair(num1, num2);
			}
			large_half_pairs.push_back(num_pair);
			std::advance(first, 2);
		}
		return large_half_pairs;
	}

	PmergeMe::ListItr BinarySearch(
		std::list<PmergeMe::LNumPair> &sorted_nums,
		const PmergeMe::LNum          &insert_num,
		std::size_t                    idx_left,
		std::size_t                    idx_right,
		PmergeMe::ListItr              itr_right
	) {
		PmergeMe::ListItr itr_left = sorted_nums.begin();

		while (idx_left < idx_right) {
			const std::size_t middle_idx = (idx_left + idx_right) / 2;
			PmergeMe::ListItr itr_middle = itr_left;
			std::advance(itr_middle, middle_idx - idx_left);

			if (middle_idx >= sorted_nums.size() || insert_num < itr_middle->large) {
				idx_right = middle_idx;
				itr_right = itr_middle;
			} else {
				idx_left = middle_idx + 1;
				itr_left = Next(itr_middle);
			}
		}
		return itr_left;
	}

	PmergeMe::ListItr InsertNumWithBinarySearch(
		std::list<PmergeMe::LNumPair> &sorted_nums,
		const PmergeMe::LNum          &insert_num,
		std::size_t                    idx_large_group_last,
		PmergeMe::ListItr              itr_sorted_last
	) {
		PmergeMe::ListItr pos = BinarySearch(
			sorted_nums, insert_num, 0, idx_large_group_last, itr_sorted_last
		);
		sorted_nums.insert(pos, GetNumPair(insert_num));
		return pos;
	}

	// insert right to left in each group
	std::list<PmergeMe::LNumPair> &InsertSmallerNumsWithEachGroup(
		unsigned int                              group_size,
		unsigned int                              total_group_size,
		PmergeMe::ListItr                         itr_sorted_last,
		std::list<PmergeMe::LNum>::const_iterator itr_insert_last,
		std::list<PmergeMe::LNumPair>            &sorted_nums
	) {
		// 1 + : already inserted front
		const unsigned int offset               = 1 + total_group_size - group_size;
		std::size_t        idx_large_group_last = offset + total_group_size;

		while (group_size) {
			const PmergeMe::LNum    insert_num = *itr_insert_last;
			const PmergeMe::ListItr pos        = InsertNumWithBinarySearch(
                sorted_nums, insert_num, idx_large_group_last, itr_sorted_last
            );
			if (pos == itr_sorted_last) {
				--idx_large_group_last;
				--itr_sorted_last;
			}
			--itr_insert_last;
			--group_size;
		}
		return sorted_nums;
	}

	void UpdateGroupSize(
		unsigned int &group_size,
		unsigned int &total_group_size,
		std::size_t   insert_small_nums_size
	) {
		total_group_size += group_size;
		if (total_group_size <= insert_small_nums_size) {
			return;
		}
		const unsigned int over = total_group_size - insert_small_nums_size;
		group_size -= over;
		total_group_size -= over;
	}

	std::list<PmergeMe::LNumPair> InsertSmallerNumsByGroup(
		std::list<PmergeMe::LNumPair>   &sorted_nums,
		const std::list<PmergeMe::LNum> &insert_small_nums
	) {
		// insert front
		sorted_nums.insert(
			sorted_nums.begin(), GetNumPair(insert_small_nums.front())
		);

		// insert front+1~
		std::size_t       insert_small_nums_size = insert_small_nums.size() - 1;
		unsigned int      total_group_size       = 0;
		PmergeMe::ListItr itr_sorted_last        = ++sorted_nums.begin();
		std::list<PmergeMe::LNum>::const_iterator itr_insert_last =
			insert_small_nums.begin();

		for (std::size_t i = 1; total_group_size < insert_small_nums_size; i++) {
			unsigned int group_size = GetJacobsthalNum(i);
			UpdateGroupSize(group_size, total_group_size, insert_small_nums_size);
			// after update group_size
			std::advance(itr_sorted_last, group_size);
			std::advance(itr_insert_last, group_size);
			sorted_nums = InsertSmallerNumsWithEachGroup(
				group_size,
				total_group_size,
				itr_sorted_last,
				itr_insert_last,
				sorted_nums
			);
		}
		return sorted_nums;
	}

	// binary search & insert smaller numbers
	std::list<PmergeMe::LNumPair> &InsertSmallerNums(
		std::list<PmergeMe::LNumPair>       &sorted_nums,
		const std::list<PmergeMe::LNumPair> &pre_num_pairs,
		std::list<PmergeMe::LNumPair>       &num_pairs
	) {
		const std::list<PmergeMe::LNum> insert_small_nums =
			MakeInsertSmallNums(sorted_nums, pre_num_pairs, num_pairs);

		sorted_nums = InsertSmallerNumsByGroup(sorted_nums, insert_small_nums);
		return sorted_nums;
	}

	std::list<PmergeMe::LNumPair> MergeInsertSortWithList(
		std::list<PmergeMe::LNumPair> &num_pairs, std::size_t nums_size
	) {
		if (num_pairs.size() == 1) {
			std::list<PmergeMe::LNumPair> result_vec;
			result_vec.push_back(GetNumPair(num_pairs.begin()->large));
			return result_vec;
		}

		// merge
		std::list<PmergeMe::LNumPair> large_half_pairs = MargeLargerPair(num_pairs);

		// recursive sort
		std::list<PmergeMe::LNumPair> sorted_nums =
			MergeInsertSortWithList(large_half_pairs, nums_size);
		if (sorted_nums.size() == nums_size) {
			return sorted_nums;
		}

		// insert
		sorted_nums = InsertSmallerNums(sorted_nums, large_half_pairs, num_pairs);
		return sorted_nums;
	}

	// ------------------------------------------------------------------------
	std::list<PmergeMe::LNumPair> ConvertToPairs(const PmergeMe::PmergeList &nums) {
		std::list<PmergeMe::LNumPair> num_pairs;

		// set LNum.num
		PmergeMe::PmergeList::const_iterator first = nums.begin();
		for (; first != nums.end(); ++first) {
			PmergeMe::LNum num;
			num.num                     = *first;
			PmergeMe::LNumPair num_pair = GetNumPair(num);
			num_pairs.push_back(num_pair);
		}
		// set self iterator to LNum.itr
		PmergeMe::ListItr pair_first = num_pairs.begin();
		for (; pair_first != num_pairs.end(); ++pair_first) {
			pair_first->small.itr = pair_first;
			pair_first->large.itr = pair_first;
		}
		return num_pairs;
	}

	PmergeMe::PmergeList
	ConvertToList(const std::list<PmergeMe::LNumPair> &result_pairs) {
		PmergeMe::PmergeList result_vec;

		std::list<PmergeMe::LNumPair>::const_iterator first = result_pairs.begin();
		for (; first != result_pairs.end(); ++first) {
			result_vec.push_back(first->large.num);
		}
		return result_vec;
	}
} // namespace sort_list

PmergeMe::PmergeList PmergeMe::MergeInsertSort(const PmergeList &nums) {
	std::list<LNumPair> nums_pair = sort_list::ConvertToPairs(nums);
	std::list<LNumPair> result_pairs =
		sort_list::MergeInsertSortWithList(nums_pair, nums.size());
	return sort_list::ConvertToList(result_pairs);
}

// ----------------------------------------------------------------------------
// debug
// ----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &out, const PmergeMe::PmergeVec &nums) {
	typename PmergeMe::PmergeVec::const_iterator begin = nums.begin();
	for (; begin != nums.end(); ++begin) {
		out << *begin << " ";
	}
	return out;
}

std::ostream &
operator<<(std::ostream &out, const std::vector<PmergeMe::VNumPair> &num_pairs) {
	typename std::vector<PmergeMe::VNumPair>::const_iterator begin =
		num_pairs.begin();
	for (; begin != num_pairs.end(); ++begin) {
		out << "{" << begin->large.num << "(" << begin->large.index << "), "
			<< begin->small.num << "(" << begin->small.index << ")} ";
	}
	return out;
}

std::ostream &
operator<<(std::ostream &out, const std::vector<PmergeMe::VNum> &nums) {
	typename std::vector<PmergeMe::VNum>::const_iterator begin = nums.begin();
	out << "[";
	for (; begin != nums.end(); ++begin) {
		out << begin->num << "(" << begin->index << "), ";
	}
	out << "]";
	return out;
}

std::ostream &operator<<(std::ostream &out, const std::list<PmergeMe::LNum> &nums) {
	typename std::list<PmergeMe::LNum>::const_iterator begin = nums.begin();
	out << "{";
	for (; begin != nums.end(); ++begin) {
		out << begin->num << " ";
	}
	out << "}";
	return out;
}

std::ostream &
operator<<(std::ostream &out, const std::list<PmergeMe::LNumPair> &num_pairs) {
	typename std::list<PmergeMe::LNumPair>::const_iterator begin = num_pairs.begin();
	out << "{";
	for (; begin != num_pairs.end(); ++begin) {
		out << "(" << begin->large.num << " " << begin->small.num << "), ";
	}
	out << "}";
	return out;
}

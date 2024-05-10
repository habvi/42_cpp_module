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

// todo
PmergeMe::PmergeVec PmergeMe::MergeInsertSort(const PmergeVec &nums) {
	PmergeVec tmp_vec = nums;
	std::sort(tmp_vec.begin(), tmp_vec.end());
	return tmp_vec;
}

// todo
PmergeMe::PmergeList PmergeMe::MergeInsertSort(const PmergeList &nums) {
	PmergeMe::PmergeList tmp_list(nums);
	tmp_list.sort();
	return tmp_list;
}

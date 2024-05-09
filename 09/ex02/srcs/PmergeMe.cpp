#include "PmergeMe.hpp"
#include <algorithm> // todo: rm (sort)

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) {
	(void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
	if (this != &other) {
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

// todo
PmergeMe::PmergeVec PmergeMe::MergeInsertSort(const PmergeVec &pmerge_vec) {
	PmergeVec tmp_vec = pmerge_vec;
	std::sort(tmp_vec.begin(), tmp_vec.end());
	return tmp_vec;
}

// todo
PmergeMe::PmergeList PmergeMe::MergeInsertSort(const PmergeList &pmerge_list) {
	PmergeMe::PmergeList tmp_list(pmerge_list);
	tmp_list.sort();
	return tmp_list;
}

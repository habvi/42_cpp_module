#include "PmergeMe.hpp"

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
	return pmerge_vec;
}

// todo
PmergeMe::PmergeList PmergeMe::MergeInsertSort(const PmergeList &pmerge_list) {
	return pmerge_list;
}

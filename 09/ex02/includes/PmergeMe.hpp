#ifndef EX02_PMERGE_ME_HPP
#define EX02_PMERGE_ME_HPP

#include <list>
#include <vector>

class PmergeMe {
  public:
	typedef std::vector<unsigned int> PmergeVec;
	typedef std::list<unsigned int>   PmergeList;
	static PmergeVec                  MergeInsertSort(const PmergeVec &nums);
	static PmergeList                 MergeInsertSort(const PmergeList &nums);

  private:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
};

#endif /* EX02_PMERGE_ME_HPP */

#ifndef EX02_PMERGE_ME_HPP
#define EX02_PMERGE_ME_HPP

#include <list>
#include <vector>

class PmergeMe {
  public:
	typedef std::vector<unsigned int> PmergeVec;
	typedef std::list<unsigned int>   PmergeList;
	static PmergeVec                  MergeInsertSort(const PmergeVec &pmerge_vec);
	static PmergeList                 MergeInsertSort(const PmergeList &pmerge_list);

  private:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
};

#endif /* EX02_PMERGE_ME_HPP */

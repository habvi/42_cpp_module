#ifndef EX02_PMERGE_ME_HPP
#define EX02_PMERGE_ME_HPP

#include <list>
#include <ostream>
#include <vector>

class PmergeMe {
  public:
	// for 1st container
	typedef std::vector<unsigned int> PmergeVec;
	struct VNum {
		unsigned int num;
		std::size_t  index;
	};
	struct VNumPair {
		VNum small;
		VNum large;
	};
	static PmergeVec MergeInsertSort(const PmergeVec &nums);

	// for 2nd container
	typedef std::list<unsigned int> PmergeList;
	struct LNumPair;
	struct LNum {
		unsigned int                  num;
		std::list<LNumPair>::iterator itr;
	};
	struct LNumPair {
		LNum small;
		LNum large;
	};
	typedef std::list<LNumPair>::iterator ListItr;
	static PmergeList                     MergeInsertSort(const PmergeList &nums);

  private:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
};

// for 1st container
std::ostream &operator<<(std::ostream &out, const PmergeMe::PmergeVec &nums);
std::ostream &operator<<(std::ostream &out, const std::vector<PmergeMe::VNum> &nums);
std::ostream &
operator<<(std::ostream &out, const std::vector<PmergeMe::VNumPair> &num_pairs);

// for 2nd container
std::ostream &operator<<(std::ostream &out, const std::list<PmergeMe::LNum> &nums);
std::ostream &
operator<<(std::ostream &out, const std::list<PmergeMe::LNumPair> &num_pairs);

#endif /* EX02_PMERGE_ME_HPP */

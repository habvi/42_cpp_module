#ifndef EX02_PMERGE_ME_HPP
#define EX02_PMERGE_ME_HPP

#include <list>
#include <ostream>
#include <vector>

class PmergeMe {
  public:
	// for 1st container
	typedef std::vector<unsigned int> PmergeVec;
	struct Num {
		unsigned int num;
		std::size_t  index;
	};
	struct NumPair {
		Num small;
		Num large;
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
std::ostream &
operator<<(std::ostream &out, const std::vector<PmergeMe::NumPair> &num_pairs);
std::ostream &operator<<(std::ostream &out, const std::vector<PmergeMe::Num> &nums);

// for 2nd container
std::ostream &operator<<(std::ostream &out, const std::list<PmergeMe::LNum> &nums);
std::ostream &
operator<<(std::ostream &out, const std::list<PmergeMe::LNumPair> &num_pairs);

#endif /* EX02_PMERGE_ME_HPP */

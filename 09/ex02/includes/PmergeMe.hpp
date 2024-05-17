#ifndef EX02_PMERGE_ME_HPP
#define EX02_PMERGE_ME_HPP

#include <list>
#include <ostream>
#include <vector>

class PmergeMe {
  public:
	typedef std::vector<unsigned int> PmergeVec;
	typedef std::list<unsigned int>   PmergeList;
	typedef struct s_num {
		unsigned int num;
		std::size_t  index;
	} Num;
	typedef struct {
		Num small;
		Num large;
	} NumPair;
	static PmergeVec  MergeInsertSort(const PmergeVec &nums);
	static PmergeList MergeInsertSort(const PmergeList &nums);

  private:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
};

std::ostream &operator<<(std::ostream &out, const PmergeMe::PmergeVec &nums);
std::ostream &
operator<<(std::ostream &out, const std::vector<PmergeMe::NumPair> &num_pairs);
std::ostream &operator<<(std::ostream &out, const std::vector<PmergeMe::Num> &nums);

#endif /* EX02_PMERGE_ME_HPP */

#ifndef EX02_MUTANTSTACK_HPP
#define EX02_MUTANTSTACK_HPP

#include <cstddef>
#include <ostream>
#include <stack>

template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container> {
  public:
	typedef typename Container::iterator               iterator;
	typedef typename Container::const_iterator         const_iterator;
	typedef typename Container::reverse_iterator       reverse_iterator;
	typedef typename Container::const_reverse_iterator const_reverse_iterator;

  public:
	MutantStack();
	MutantStack(const MutantStack &other);
	MutantStack &operator=(const MutantStack &other);
	~MutantStack();

  public:
	iterator               begin();
	const_iterator         begin() const;
	iterator               end();
	const_iterator         end() const;
	reverse_iterator       rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator       rend();
	const_reverse_iterator rend() const;

  public:
	std::ostream &Print(std::ostream &out) const;
};

template <typename T, typename Container>
std::ostream &operator<<(std::ostream &out, const MutantStack<T, Container> &m);

#include "MutantStack.tpp"

#endif /* EX02_MUTANTSTACK_HPP */

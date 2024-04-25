#ifndef EX02_MUTANTSTACK_HPP
#define EX02_MUTANTSTACK_HPP

#include <cstddef>
#include <stack>

template <typename T>
class MutantStack : public std::stack<T> {
  public:
	typedef typename std::deque<T>::iterator       iterator;
	typedef typename std::deque<T>::const_iterator const_iterator;

  public:
	MutantStack();
	MutantStack(const MutantStack &other);
	MutantStack &operator=(const MutantStack &other);
	~MutantStack();

  public:
	iterator       begin();
	const_iterator begin() const;
	iterator       end();
	const_iterator end() const;
	std::size_t    size() const;

  public:
	void DebugPrint();
};

#include "MutantStack.tpp"

#endif /* EX02_MUTANTSTACK_HPP */

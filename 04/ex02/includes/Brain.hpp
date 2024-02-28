#ifndef EX02_BRAIN_HPP
#define EX02_BRAIN_HPP

#include <string>

class Brain {
  public:
	Brain();
	Brain(const Brain &b);
	const Brain &operator=(const Brain &b);
	~Brain();

  public:
	unsigned int       GetNumOfIdeas() const;
	const std::string &GetIthIdea(const unsigned int index) const;
	void               SetIthIdea(const unsigned int index, const std::string &idea);

  private:
	void CopyIdeas(const Brain &b);

  private:
	static const unsigned int kNumOfIdea = 100;
	// Following the instructions, no underscore.
	std::string ideas[kNumOfIdea];
};

#endif /* EX02_BRAIN_HPP */

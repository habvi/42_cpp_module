#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>

#define COLOR_RED          "\033[31m"
#define COLOR_PINK         "\033[35m"
#define COLOR_END          "\033[0m"

#define ZOMBIE_SOUND       "BraiiiiiiinnnzzzZ..."
#define ZOMBIE_DEAD        " is dead."
#define ERR_NUM_OF_ZOMBIES "invalid number of zombies"
#define ERR_ALLOCATE       "allocation failed"

class Zombie {
  public:
	Zombie();
	explicit Zombie(const std::string &name);
	explicit Zombie(const Zombie &z);
	~Zombie();

  public:
	// Following the instructions, not camelcase.
	void announce(void) const;

  private:
	std::string name_;
};

// Following the instructions, not camelcase.
Zombie *zombieHorde(int numOfZombies, std::string name);

#endif /* ZOMBIE_H */

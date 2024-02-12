#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>

#define COLOR_RED    "\033[31m"
#define COLOR_PINK   "\033[35m"
#define COLOR_END    "\033[0m"

#define ZOMBIE_SOUND "BraiiiiiiinnnzzzZ..."
#define ZOMBIE_DEAD  " is dead."

class Zombie {
  public:
	explicit Zombie(const std::string &name);
	~Zombie();

  public:
	void announce(void) const;

  private:
	Zombie();

  private:
	std::string name_;
};

Zombie *newZombie(std::string name);
void    randomChump(std::string name);

#endif /* ZOMBIE_H */

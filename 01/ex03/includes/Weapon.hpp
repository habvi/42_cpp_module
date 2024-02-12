#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon {
  public:
	explicit Weapon(const std::string &type);
	~Weapon();

  public:
	// Following the instructions, not camelcase.
	const std::string &getType() const;
	void               setType(const std::string &newType);

  private:
	Weapon();

  private:
	std::string type_;
};

#endif /* WEAPON_H */

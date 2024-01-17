#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Weapon {
  public:
	Weapon();
	explicit Weapon(const std::string &type);
	~Weapon();

  public:
	const std::string &getType() const;
	void               setType(const std::string &newType);

  private:
	std::string type_;
};

#endif /* WEAPON_H */

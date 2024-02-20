#ifndef CLAP_TRAP_H
#define CLAP_TRAP_H

#include <string>

class ClapTrap {
  public:
	explicit ClapTrap(const std::string &name);
	ClapTrap(const std::string &name, const unsigned int hit_point);
	ClapTrap(const ClapTrap &c);
	~ClapTrap();
	const ClapTrap &operator=(const ClapTrap &c);

  public:
	// Following the instructions, not camelcase.
	void attack(const std::string &target);
	void takeDamage(unsigned int amount);
	void btRepaired(unsigned int amount);

  public:
	void PutStatus() const;
	bool IsActionPossible() const;
	void LoseEnergyPoint();

  public:
	const std::string &GetName() const;
	unsigned int       GetHitPoints() const;
	unsigned int       GetEnergyPoints() const;
	unsigned int       GetAttackDamage() const;
	void               SetAttackDamage(const unsigned int damages);

  private:
	ClapTrap();

  private:
	std::string  name_;
	unsigned int hit_points_;
	unsigned int energy_points_;
	unsigned int attack_damage_;
};

#endif /* CLAP_TRAP_H */

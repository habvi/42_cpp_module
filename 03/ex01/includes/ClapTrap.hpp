#ifndef CLAP_TRAP_H
#define CLAP_TRAP_H

#include <string>

class ClapTrap {
  public:
	explicit ClapTrap(const std::string &name);
	ClapTrap(const ClapTrap &c);
	~ClapTrap();
	ClapTrap &operator=(const ClapTrap &c);

  public:
	// Following the instructions, not camelcase.
	virtual void attack(const std::string &target);
	void         takeDamage(unsigned int amount);
	void         beRepaired(unsigned int amount);

  public:
	void AttackToDefender(
		ClapTrap &defender, const std::string &target, const unsigned int damages
	);
	void PutStatus() const;
	bool IsActionPossible() const;
	void LoseEnergyPoint();

  public:
	const std::string &GetName() const;
	unsigned int       GetHitPoints() const;
	unsigned int       GetEnergyPoints() const;
	unsigned int       GetAttackDamage() const;
	void               SetAttackDamage(const unsigned int damages);

  protected:
	ClapTrap();
	void SetHitPoints(const unsigned int hit_points);
	void SetEnergyPoints(const unsigned int energy_points);

  private:
	std::string  name_;
	unsigned int hit_points_;
	unsigned int energy_points_;
	unsigned int attack_damage_;

	static const unsigned int kInitialHitPoints    = 10;
	static const unsigned int kInitialEnergyPoints = 10;
	static const unsigned int kInitialAttackDamage = 0;
};

#endif /* CLAP_TRAP_H */

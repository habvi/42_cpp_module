#include "Weapon.hpp"
#include <string>

Weapon::Weapon() {
	type_.clear();
}

Weapon::Weapon(const std::string &type) {
	type_ = type;
}

Weapon::~Weapon() {}

const std::string &Weapon::getType() const {
	return type_;
}

void Weapon::setType(const std::string &newType) {
	type_ = newType;
}

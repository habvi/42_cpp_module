#include "Character.hpp"
#include "AMateria.hpp"

void Character::initMaterias() {
	for (unsigned int i = 0; i < kLimitSlotNum; i++) {
		slot_[i] = NULL;
	}
}

Character::Character() {
	initMaterias();
}

Character::Character(const std::string &name) : name_(name) {
	initMaterias();
}

void Character::copyMaterias(const Character &c) {
	// assert
	for (unsigned int i = 0; i < kLimitSlotNum; i++) {
		if (c.slot_[i]) {
			slot_[i] = c.slot_[i]->clone();
			// todo: throw exception
		} else {
			slot_[i] = NULL;
		}
	}
}
Character::Character(const Character &c) : name_(c.getName()) {
	// todo: try-catch
	copyMaterias(c);
}

const Character &Character::operator=(const Character &c) {
	if (this != &c) {
		name_ = c.getName();
		for (unsigned int i = 0; i < kLimitSlotNum; i++) {
			delete slot_[i];
		}
		// todo: try-catch
		copyMaterias(c);
	}
	return *this;
}

Character::~Character() {
	for (unsigned int i = 0; i < kLimitSlotNum; i++) {
		delete slot_[i];
	}
}

void Character::equip(AMateria *a) {
	if (a == NULL) {
		return;
	}
	for (unsigned int i = 0; i < kLimitSlotNum; i++) {
		if (slot_[i] == NULL) {
			slot_[i] = a;
			return;
		}
	}
}

bool Character::isValidIndex(const int index) const {
	return index >= 0 && static_cast<unsigned int>(index) < kLimitSlotNum;
}

void Character::unequip(int index) {
	if (!isValidIndex(index)) {
		// todo: cerr? (don’t do anything..)
		return;
	}
	slot_[index] = NULL;
}

void Character::use(int index, ICharacter &target) {
	if (!isValidIndex(index)) {
		return;
	}
	if (slot_[index] == NULL) {
		return;
	}
	slot_[index]->use(target);
}

const std::string &Character::getName() const {
	return name_;
}

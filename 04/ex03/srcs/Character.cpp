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
	for (unsigned int i = 0; i < kLimitSlotNum; i++) {
		if (c.slot_[i]) {
			slot_[i] = c.slot_[i]->clone();
			if (slot_[i] == NULL) {
				throw std::bad_alloc();
			}
		} else {
			slot_[i] = NULL;
		}
	}
}
Character::Character(const Character &c) : name_(c.getName()) {
	try {
		copyMaterias(c);
	} catch (const std::bad_alloc &e) {
		throw;
	}
}

Character &Character::operator=(const Character &c) {
	if (this != &c) {
		name_ = c.getName();
		for (unsigned int i = 0; i < kLimitSlotNum; i++) {
			delete slot_[i];
		}
		try {
			copyMaterias(c);
		} catch (const std::bad_alloc &e) {
			throw;
		}
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

unsigned int Character::getLimitSlotNum() const {
	return kLimitSlotNum;
}

AMateria *Character::getIthAMateria(const unsigned int index) const {
	if (!isValidIndex(index)) {
		return NULL;
	}
	return slot_[index];
}

#include "Harl.hpp"
#include <iostream>
#include <string>

Harl::Harl() {}

Harl::~Harl() {}

static void PutKind(const std::string &kind) {
	std::cout << "[ " << kind << " ]" << std::endl;
}

static void PutMessage(const std::string &message) {
	std::cout << message << std::endl << std::endl;
}

void Harl::debug(void) {
	PutKind(kDebug_);
	static const std::string kMessage =
		"I love having extra bacon for my "
		"7XL-double-cheese-triple-pickle-specialketchup burger. I really do!";
	PutMessage(kMessage);
}

void Harl::info(void) {
	PutKind(kInfo_);
	static const std::string kMessage =
		"I cannot believe adding extra bacon costs more money. You didn’t put "
		"enough bacon in my burger! If you did, I wouldn’t be asking for more!";
	PutMessage(kMessage);
}

void Harl::warning(void) {
	PutKind(kWarning_);
	static const std::string kMessage =
		"I think I deserve to have some extra bacon for free. I’ve been coming for "
		"years whereas you started working here since last month.";
	PutMessage(kMessage);
}

void Harl::error(void) {
	PutKind(kError_);
	static const std::string kMessage =
		"This is unacceptable! I want to speak to the manager now.";
	PutMessage(kMessage);
}

static void PutInvalidLevel() {
	static const std::string kMessage =
		"Probably complaining about insignificant problems";
	PutKind(kMessage);
}

void Harl::SetComplains(Pair *complains) {
	complains[kLevelDebug]   = std::make_pair(kDebug_, &Harl::debug);
	complains[kLevelInfo]    = std::make_pair(kInfo_, &Harl::info);
	complains[kLevelWarning] = std::make_pair(kWarning_, &Harl::warning);
	complains[kLevelError]   = std::make_pair(kError_, &Harl::error);
}

unsigned int Harl::SetLevel(const Pair *complains, const std::string &level) {
	for (unsigned int i = 0; i < kTotalLevel_; i++) {
		if (level == complains[i].first) {
			return i;
		}
	}
	return kTotalLevel_;
}

void Harl::Filter(std::string level) {
	static Pair complains[kTotalLevel_];
	SetComplains(complains);

	const Level complain_level = static_cast<Level>(SetLevel(complains, level));

	switch (complain_level) {
	case kLevelDebug:
		(this->*(complains[kLevelDebug].second))();
		/* fallthrough */
	case kLevelInfo:
		(this->*(complains[kLevelInfo].second))();
		/* fallthrough */
	case kLevelWarning:
		(this->*(complains[kLevelWarning].second))();
		/* fallthrough */
	case kLevelError:
		(this->*(complains[kLevelError].second))();
		return;
	default:
		PutInvalidLevel();
	}
}

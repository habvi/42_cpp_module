#include "Brain.hpp"
#include "color.hpp"
#include <iostream>
#include <string>

#define TYPE_BRAIN "Brain"

Brain::Brain() {
	std::cerr << "Default constructor called (" TYPE_BRAIN ")" << std::endl;
}

void Brain::CopyIdeas(const Brain &b) {
	std::cerr << "Constructor called (" TYPE_BRAIN ")" << std::endl;
	for (unsigned int i = 0; i < kNumOfIdea; i++) {
		ideas[i] = b.ideas[i];
	}
}

Brain::Brain(const Brain &b) {
	std::cerr << "Coppy constructor called (" TYPE_BRAIN ")" << std::endl;
	CopyIdeas(b);
}

const Brain &Brain::operator=(const Brain &b) {
	std::cerr << "Copy assignment operator= called (" TYPE_BRAIN ")" << std::endl;
	if (this != &b) {
		CopyIdeas(b);
	}
	return *this;
}

Brain::~Brain() {
	std::cerr << "Destructor called (" TYPE_BRAIN ")" << std::endl;
}

unsigned int Brain::GetNumOfIdeas() const {
	return kNumOfIdea;
}

const std::string &Brain::GetIthIdea(const unsigned int index) const {
	if (index >= kNumOfIdea) {
		throw std::out_of_range(COLOR_RED "Error: index out of range" COLOR_END);
	}
	return ideas[index];
}

void Brain::SetIthIdea(const unsigned int index, const std::string &idea) {
	if (index >= kNumOfIdea) {
		throw std::out_of_range(COLOR_RED "Error: index out of range" COLOR_END);
	}
	ideas[index] = idea;
}

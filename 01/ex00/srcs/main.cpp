#include "Zombie.hpp"
#include <cstdlib>
#include <iostream>

static void DisplayTitle(const std::string &title) {
	std::cout << "┃ test: " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void Line() {
	std::cout << "--------------------------------" << std::endl;
}

static void TestRandomChump() {
	DisplayTitle("randomChump()");

	randomChump("a");
	Line();
	randomChump("");
	Line();
	randomChump("bb");

	std::cout << std::endl;
}

static void CallNewZombieAndAnnounce(const std::string &name) {
	Zombie *zombie = newZombie(name);
	if (zombie == NULL) {
		std::cerr << COLOR_RED "Error: allocation failed" COLOR_END << std::endl;
		exit(EXIT_FAILURE);
	}
	zombie->announce();
	delete zombie;
}

static void TestNewZombie() {
	DisplayTitle("newZombie(), announce()");

	CallNewZombieAndAnnounce("ccc");
	Line();
	CallNewZombieAndAnnounce("");
	Line();
	CallNewZombieAndAnnounce("abcdefghijk");
}

int main() {
	TestRandomChump();
	TestNewZombie();
	return EXIT_SUCCESS;
}

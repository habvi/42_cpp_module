#include "Zombie.hpp"
#include <cstdlib>
#include <iostream>

static void displayTitle(const std::string &title) {
	std::cout << "┃ test: " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void line() {
	std::cout << "--------------------------------" << std::endl;
}

static void testRandomChump() {
	displayTitle("randomChump()");

	randomChump("a");
	line();
	randomChump("");
	line();
	randomChump("bb");

	std::cout << std::endl;
}

static void callNewZombieAndAnnounce(const std::string &name) {
	Zombie *zombie = newZombie(name);
	if (zombie == NULL) {
		std::cerr << COLOR_RED "Error: allocation failed" COLOR_END << std::endl;
		exit(EXIT_FAILURE);
	}
	zombie->announce();
	delete zombie;
}

static void testNewZombie() {
	displayTitle("newZombie(), announce()");

	callNewZombieAndAnnounce("ccc");
	line();
	callNewZombieAndAnnounce("");
	line();
	callNewZombieAndAnnounce("abcdefghijk");
}

int main() {
	testRandomChump();
	testNewZombie();
	return EXIT_SUCCESS;
}

#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"
#include "color.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>

Base *generate(void) {
	const int random_num = std::rand() % 3;
	Base     *base;

	std::cout << COLOR_PINK "Generate type : ";
	if (random_num == 0) {
		std::cout << "A";
		base = new A();
	} else if (random_num == 1) {
		std::cout << "B";
		base = new B();
	} else {
		std::cout << "C";
		base = new C();
	}
	std::cout << COLOR_END << std::endl;
	return base;
}

void print(const std::string &type) {
	std::cout << "Actual type is: " COLOR_GREEN << type << COLOR_END << std::endl;
}

void identify(Base *p) {
	if (p == NULL) {
		throw std::invalid_argument("argument is NULL");
	}
	if (dynamic_cast<A *>(p)) {
		print("A");
	} else if (dynamic_cast<B *>(p)) {
		print("B");
	} else if (dynamic_cast<C *>(p)) {
		print("C");
	} else {
		throw std::invalid_argument("invalid argument type");
	}
}

int main() {
	std::srand(std::time(0));

	Base *p = generate();
	identify(p);
	delete p;

	std::cout << "------------------" << std::endl;
	// try passed NULL
	try {
		identify(NULL);
	} catch (const std::exception &e) {
		std::cerr << COLOR_RED << e.what() << COLOR_END << std::endl;
	}

	return EXIT_SUCCESS;
}

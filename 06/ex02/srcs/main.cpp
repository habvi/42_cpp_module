#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"
#include "color.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

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

int main() {
	std::srand(std::time(0));

	Base *p = generate();
	delete p;
	return EXIT_SUCCESS;
}

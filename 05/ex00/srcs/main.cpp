#include "Bureaucrat.hpp"
#include <iostream>

int main() {
	Bureaucrat b("Alice", 123);
	std::cout << b.getName() << std::endl;
	std::cout << b.getGrade() << std::endl;

	Bureaucrat b2 = Bureaucrat("Bob", 5);
	std::cout << b2.getName() << std::endl;
	std::cout << b2.getGrade() << std::endl;

	Bureaucrat b3 = b;
	std::cout << b3.getName() << std::endl;
	std::cout << b3.getGrade() << std::endl;
}

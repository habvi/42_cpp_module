#include "iter.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

template <typename T>
static void PutArray(const std::string &title, const T &array) {
	std::cout << title << " = {";
	const size_t size = sizeof(array) / sizeof(*array);
	for (size_t i = 0; i < size; i++) {
		std::cout << array[i];
		if (i != size - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "}" << std::endl;
}

static void Line() {
	std::cout << "----------------------------" << std::endl;
}

// -------------------------------------------------
template <typename T>
void ToDouble(T &x) {
	x *= 2;
}

static void RunTest1() {
	int array[5] = {-1, 0, 1, 2, 3};
	PutArray("before", array);

	iter(array, 5, &ToDouble);
	PutArray("after ", array);
}

// -------------------------------------------------
template <typename T>
void AddBikkuri(T &s) {
	s += "!";
}

static void RunTest2() {
	std::string array[3] = {"", "x", "abcde"};
	PutArray("before", array);

	iter(array, 3, &AddBikkuri);
	PutArray("after ", array);
}

// -------------------------------------------------
template <typename T>
void Nothing(const T &a) {
	(void)a;
}

static void RunTest3() {
	const std::string array[3] = {"", "x", "abcde"};
	PutArray("before", array);

	iter(array, 3, &Nothing);
	PutArray("after ", array);
}

// -------------------------------------------------
int main() {
	RunTest1();
	Line();
	RunTest2();
	Line();
	RunTest3();
	return EXIT_SUCCESS;
}

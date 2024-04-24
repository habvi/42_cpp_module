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

template <typename T>
void NonConstNothing(T &a) {
	(void)a;
}

template <typename T>
void ConstNothing(const T &a) {
	(void)a;
}
// -------------------------------------------------
// non-const int[], non-const func
static void RunTest1() {
	int array[5] = {-1, 0, 1, 2, 3};
	PutArray("before", array);

	iter(array, 5, &ToDouble);
	PutArray("after ", array);
}

// non-const int[], const func
static void RunTest2() {
	int array[5] = {-1, 0, 1, 2, 3};
	PutArray("before", array);

	iter(array, 5, &ConstNothing);
	PutArray("after ", array);
}

// const int[], non-const func
static void RunTest3() {
	const int array[5] = {-1, 0, 1, 2, 3};
	PutArray("before", array);

	iter(array, 5, &NonConstNothing);
	PutArray("after ", array);
}

// const int[], const func
static void RunTest4() {
	const int array[5] = {-1, 0, 1, 2, 3};
	PutArray("before", array);

	iter(array, 5, &ConstNothing);
	PutArray("after ", array);
}

// -------------------------------------------------
template <typename T>
void AddBikkuri(T &s) {
	s += "!";
}

// -------------------------------------------------
// non-const string[], non-const func
static void RunTest5() {
	std::string array[3] = {"", "x", "abcde"};
	PutArray("before", array);

	iter(array, 3, &AddBikkuri);
	PutArray("after ", array);
}

// non-const string[], const func
static void RunTest6() {
	std::string array[3] = {"", "x", "abcde"};
	PutArray("before", array);

	iter(array, 3, &ConstNothing);
	PutArray("after ", array);
}

// const string[], non-const func
static void RunTest7() {
	const std::string array[3] = {"", "x", "abcde"};
	PutArray("before", array);

	iter(array, 3, &NonConstNothing);
	PutArray("after ", array);
}

// const string[], const func
static void RunTest8() {
	const std::string array[3] = {"", "x", "abcde"};
	PutArray("before", array);

	iter(array, 3, &ConstNothing);
	PutArray("after ", array);
}

// -------------------------------------------------
int main() {
	RunTest1();
	Line();
	RunTest2();
	Line();
	RunTest3();
	Line();
	RunTest4();
	Line();
	RunTest5();
	Line();
	RunTest6();
	Line();
	RunTest7();
	Line();
	RunTest8();
	return EXIT_SUCCESS;
}

#include "iter.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

namespace test {
	template <typename T>
	void
	PutArray(const std::string &title, const T &array, const size_t array_size) {
		std::cout << title << " = {";
		for (size_t i = 0; i < array_size; i++) {
			std::cout << array[i];
			if (i != array_size - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "}" << std::endl;
	}

	void Line() {
		std::cout << "----------------------------" << std::endl;
	}

	// -------------------------------------------------
	template <typename T>
	void ToDouble(T &x) {
		x *= 2;
	}

	template <typename T>
	void AddBikkuri(T &s) {
		s += "!";
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
	void RunTest1() {
		int array[5] = {-1, 0, 1, 2, 3};
		PutArray("before", array, 5);

		iter(array, 5, &ToDouble);
		PutArray("after ", array, 5);
		Line();
	}

	// non-const int[], const func
	void RunTest2() {
		int array[5] = {-1, 0, 1, 2, 3};
		PutArray("before", array, 5);

		iter(array, 5, &ConstNothing);
		PutArray("after ", array, 5);
		Line();
	}

	// const int[], non-const func
	void RunTest3() {
		const int array[5] = {-1, 0, 1, 2, 3};
		PutArray("before", array, 5);

		iter(array, 5, &NonConstNothing);
		PutArray("after ", array, 5);
		Line();
	}

	// const int[], const func
	void RunTest4() {
		const int array[5] = {-1, 0, 1, 2, 3};
		PutArray("before", array, 5);

		iter(array, 5, &ConstNothing);
		PutArray("after ", array, 5);
		Line();
	}

	// -------------------------------------------------
	// non-const string[], non-const func
	void RunTest5() {
		std::string array[3] = {"", "x", "abcde"};
		PutArray("before", array, 3);

		iter(array, 3, &AddBikkuri);
		PutArray("after ", array, 3);
		Line();
	}

	// non-const string[], const func
	void RunTest6() {
		std::string array[3] = {"", "x", "abcde"};
		PutArray("before", array, 3);

		iter(array, 3, &ConstNothing);
		PutArray("after ", array, 3);
		Line();
	}

	// const string[], non-const func
	void RunTest7() {
		const std::string array[3] = {"", "x", "abcde"};
		PutArray("before", array, 3);

		iter(array, 3, &NonConstNothing);
		PutArray("after ", array, 3);
		Line();
	}

	// const string[], const func
	void RunTest8() {
		const std::string array[3] = {"", "x", "abcde"};
		PutArray("before", array, 3);

		iter(array, 3, &ConstNothing);
		PutArray("after ", array, 3);
	}
} // namespace test

// -------------------------------------------------
int main() {
	test::RunTest1();
	test::RunTest2();
	test::RunTest3();
	test::RunTest4();
	test::RunTest5();
	test::RunTest6();
	test::RunTest7();
	test::RunTest8();
	return EXIT_SUCCESS;
}
